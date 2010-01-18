/*
    WebDMA
    Copyright (C) 2009-2010 Dustin Spicuzza <dustin@virtualroadside.com>
	
	$Id$

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License v3 as published by
    the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef WI_DATAPROXYINFO_H
#define WI_DATAPROXYINFO_H

#include <string>
#include <sstream>

#include <boost/lexical_cast.hpp>
#include <boost/thread/shared_mutex.hpp>

#include "VariableProxyFlags.h"
#include "VariableProxy.h"


// base type
struct DataProxyInfo {

	virtual bool SetValue( const std::string & ) = 0;
	virtual std::string GetHtmlDisplay(std::size_t, std::size_t) const = 0;
	virtual std::string GetJson(std::size_t, std::size_t) const = 0;
	virtual ~DataProxyInfo(){}

};




// numeric implementation
template <typename T, typename Proxy>
struct NumericProxyInfoImpl : public DataProxyInfo {

	typedef NumericProxyFlagsImpl<T>	Flags;

	typedef typename Proxy::mutex_type	mutex_type;
	typedef typename boost::shared_lock<mutex_type>	read_lock;
	typedef typename boost::unique_lock<mutex_type> write_lock;

	/// constructor
	NumericProxyInfoImpl(const Flags& flags) :
		m_proxied_value(flags.default_value_),
		m_flags(flags)
	{}

	/// external thing sets value
	bool SetValue( const std::string &value )
	{
		T new_value;
		
		try 
		{
			new_value = boost::lexical_cast<T>(value);
		} 
		catch (boost::bad_lexical_cast &)
		{
			return false;
		}
		
		// check bounds
		if (m_flags.readonly_ ||
			new_value < m_flags.minval_ || 
			new_value > m_flags.maxval_
		)
			return false;
		
		// finally, aquire the lock and write it out
		{
			write_lock lock(m_mutex);
			m_proxied_value = new_value;
		}
		
		return true;
	}
	
	/// returns html
	std::string GetHtmlDisplay(std::size_t gid, std::size_t vid) const
	{
		T current_value;
	
		{
			read_lock lock(m_mutex);
			current_value = m_proxied_value;
		}
	
		std::string html;
		
		// generate an id based on the flags	
		std::stringstream idstr;
		idstr.precision(m_flags.precision_);
		idstr.setf( std::ios::fixed, std::ios::floatfield );
		
		if (m_flags.readonly_)
		{
			html.append("<span class=\"readonlyvar\" id=\"g" +
				boost::lexical_cast<std::string>(gid) +
				"_v" +
				boost::lexical_cast<std::string>(vid) +
				"\">");
		}
		else
		{
			html.append("<div class=\"selectbar\" id=\"");
		
		
			idstr 	<< "g" << gid
					<< "_v" << vid
					<< "_" << current_value
					<< "_" << m_flags.minval_
					<< "_" << m_flags.maxval_
					<< "_" << m_flags.step_;
		
			std::string id = idstr.str();
			
			for (std::size_t i = 0; i < id.size(); i++)
				if (id[i] == '.')
					id[i] = 'p';
		
			html.append(id);
			html.append("\">");
		}
			
		// makes sure the value is formatted correctly
		idstr.str("");
		idstr	<< current_value;
			
		html.append(idstr.str());
		
		if (m_flags.readonly_)
			html.append("</span>");
		else
			html.append("</div>");
		
		
		return html;
	}
	
	std::string GetJson(std::size_t gid, std::size_t vid) const 
	{
		T current_value;
		
		{
			read_lock lock(m_mutex);
			current_value = m_proxied_value;
		}

		// generate an id based on the flags	
		std::stringstream json;
		json.precision(m_flags.precision_);
		json.setf( std::ios::fixed, std::ios::floatfield );
		
		json 	<< "\"g" << gid
				<< "_v" << vid
				<< "\": " << current_value;
				
		return json.str();
	}
	
	
	Proxy GetProxy()
	{
		return Proxy(&m_proxied_value, &m_mutex);
	}
	
private:
	NumericProxyInfoImpl();

	T 					m_proxied_value;
	mutable mutex_type 	m_mutex;
	const Flags			m_flags;
};

/// implementation for floats
typedef NumericProxyInfoImpl<float, FloatProxy>		FloatProxyInfo;

/// implementation for doubles
typedef NumericProxyInfoImpl<double, DoubleProxy>	DoubleProxyInfo;

/// implementation for integers
typedef NumericProxyInfoImpl<int, IntProxy> 		IntProxyInfo;



// boolean implementation
struct BoolProxyInfo : public DataProxyInfo {

	typedef BoolProxy					Proxy;

	typedef Proxy::mutex_type			mutex_type;
	typedef boost::shared_lock<mutex_type>	read_lock;
	typedef boost::unique_lock<mutex_type> write_lock;

	/// constructor
	BoolProxyInfo(bool default_value) :
		m_proxied_value(default_value)
	{}

	/// external thing sets value
	bool SetValue( const std::string &value)
	{
		try {
			write_lock lock(m_mutex);
			m_proxied_value = boost::lexical_cast<bool>(value);
		} 
		catch (boost::bad_lexical_cast &)
		{
			return false;
		}
		
		return true;
	}
	
	/// returns html
	std::string GetHtmlDisplay(std::size_t gid, std::size_t vid) const
	{
		bool current_value;
	
		{
			read_lock lock(m_mutex);
			current_value = m_proxied_value;
		}
	
		std::string html;
		
		html = "<input class=\"booleans\" type=\"checkbox\" id=\"g"
				+ boost::lexical_cast<std::string>(gid)
				+ "_v"
				+ boost::lexical_cast<std::string>(vid)
				+ (current_value ? "_checked" : "_notchecked")
				+ "\"";
				
		if (current_value)
			html.append(" checked");
		
		html.append(" />");
		
		return html;
	}
	
	std::string GetJson(std::size_t gid, std::size_t vid) const
	{
		bool current_value;
	
		{
			read_lock lock(m_mutex);
			current_value = m_proxied_value;
		}

		return "\"g"
			+ boost::lexical_cast<std::string>(gid)
			+ "_v"
			+ boost::lexical_cast<std::string>(vid)
			+ (current_value ? "\": true" : "\": false");
	}
	
	Proxy GetProxy()
	{
		return Proxy(&m_proxied_value, &m_mutex);
	}
	
private:
	BoolProxyInfo();

	bool 				m_proxied_value;
	mutable mutex_type 	m_mutex;
};




#endif
