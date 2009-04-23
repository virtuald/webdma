/*
    WebDMA
    Copyright (C) 2009 Dustin Spicuzza <dustin@virtualroadside.com>
	
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

#ifndef WI_VARIABLEPROXY_H
#define WI_VARIABLEPROXY_H

#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>


/**
	\class VariableProxyImpl

	This type allows you to use it in read-only operations exactly like
	you would use the native type. The underlying data is in some 
	configuration database or some such thing. Its like a smart pointer,
	but a bit different.

	The assumption is made that the proxy information will outlive the 
	individual proxy instances, so this just holds raw pointers to the 
	parent. This allows copying of the proxy type as much as you want, 
	though I'm not quite sure why one would want to copy it all that much. 
	
	@warning There are a number of caveats with this scheme: the primary one
	is that since this is essentially a volatile instance, the proxied
	value can change at any given time. Best practices would dictate that you
	store the variable in a temporary if you are doing multiple operations
	with the variable. Each access results in a lock operation, so accessing
	this object can be expensive as well. 
	
	@todo If we could use atomic operations, then we wouldn't need to do any
	locking and this could be quite fast
*/
template <typename T>
struct VariableProxyImpl {

	typedef boost::shared_mutex mutex_type;
	typedef boost::shared_lock< mutex_type > read_lock;
	typedef boost::unique_lock< mutex_type > write_lock;

	/// default/null constructor
	VariableProxyImpl() :
		m_proxied_value(NULL), m_mutex(NULL)
	{}
	
	/// initialization constructor
	VariableProxyImpl(T * proxied_value, mutex_type * mutex) :
		m_proxied_value(proxied_value), m_mutex(mutex)
	{}

	/// converts to the given type automatically
	operator T() const
	{
		read_lock lock(*m_mutex);
		return *m_proxied_value; 
	}
	
	/// a more explicit way of obtaining the value
	T Get() const
	{
		read_lock lock(*m_mutex);
		return *m_proxied_value; 
	}
	
	
	/// changes the variable
	VariableProxyImpl<T>& operator=(const T& value)
	{
		write_lock lock(*m_mutex);
		*m_proxied_value = value;
		return *this;
	}

	/// a more explicit way of setting the value
	void Set(const T& value)
	{
		write_lock lock(*m_mutex);
		*m_proxied_value = value;
	}

private:
	T * 					m_proxied_value;
	mutable mutex_type *	m_mutex;

};

/// definition of integer proxy
typedef VariableProxyImpl<int>		IntProxy;

/// definition of floating point proxy
typedef VariableProxyImpl<float>	FloatProxy;

/// definition of double floating point proxy
typedef VariableProxyImpl<double>	DoubleProxy;

/// definition of boolean proxy
typedef VariableProxyImpl<bool>		BoolProxy;


#endif
