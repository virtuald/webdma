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


#include "WebDMA_Pimpl.h"
#include <WebDMA/VariableProxy.h>

#include "server/server.hpp"

#include <ctime>
#include <iostream>

#include <boost/tokenizer.hpp>

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#include "StaticDeleter.h"

#define JSON_STATUS(x) "{ \"status\": \"" x "\" }"

static
WebDMA_Pimpl * m_instance = NULL;

// this ensures that the singleton WebDMA_Pimpl gets deleted at exit
StaticDeleter<WebDMA_Pimpl> m_deleter(&m_instance);


// default constructor
WebDMA_Pimpl::WebDMA_Pimpl() :
	m_port("80"),
	m_rootDir("www"),
	m_current_instance(boost::lexical_cast<std::string>(time(NULL))),
	m_server(NULL),
	m_thread_created(false)
{}

WebDMA_Pimpl::~WebDMA_Pimpl()
{
	bool thread_created = false;

	{
		lock_guard lock(m_mutex);
		thread_created = m_thread_created;
	}
	
	// if the thread is created, then join it. Be sure that
	// we don't hold the lock while it is joined, otherwise
	// the server will deadlock. the lock must be held when
	// signaling the server however. 
	if (thread_created)
	{
		{
			lock_guard lock(m_mutex);
			if (m_server)
				m_server->stop();
		}

		m_thread->join();
	}
}


/// this is the thread that the HTTP server runs on. When the WebDMA_Pimpl singleton
/// instance is destroyed, the server should be signaled to exit and the 
/// thread will be joined, at which point the object can be fully destroyed
void WebDMA_Pimpl::ThreadFn()
{
	try
	{
		// Initialise server.
		{
			lock_guard lock(m_mutex);
			m_server = new http::server::server("0.0.0.0", m_port, m_rootDir);
		}
	
		// Run the server until stopped.
		m_server->run();
	}
	catch (std::exception &e)
	{
		std::cerr << "WebDMA_Pimpl Server exception: " << e.what() << std::endl;
	}
	
	{
		lock_guard lock(m_mutex);
		delete m_server;
		m_server = NULL;
	}
}


void WebDMA_Pimpl::Enable(const std::string &port, const std::string &rootdir)
{
	lock_guard lock(m_mutex);
		
	if (!port.empty())
		m_port = port;
		
	if (!rootdir.empty())
		m_rootDir = rootdir;
		
	// then start the thread
	if (!m_thread_created)
	{
		m_thread.reset( new boost::thread(boost::bind(&WebDMA_Pimpl::ThreadFn, this)) );
		m_thread_created = true;
	}
}

// internal function
WebDMA_Pimpl * WebDMA_Pimpl::GetInstance()	
{
	if (m_instance == NULL)
		m_instance = new WebDMA_Pimpl();
	return m_instance;
}


/// this function returns the html to be inserted into the index.html page
std::string WebDMA_Pimpl::get_html()
{
	// lock globally
	lock_guard lock(m_mutex);

	// generate some HTML for this thing
	std::string html;

	size_t g = 0;
	
	foreach( const DataProxyGroupPtr &gptr  , m_groups )
	{
		// group name/header
		html.append("\n\t<div class=\"group\">\n");
		html.append("\t\t<div class=\"grouphdr\">\n");
		html.append("\t\t\t");
		html.append(gptr->name);
		html.append("\n\t\t</div>\n\t\t<div><table>\n");
		
		size_t v = 0;
		
		// for each variable, create a table row for it
		foreach( const DataProxyVariablePtr &dptr, gptr->variables )
		{
			html.append("\t\t\t<tr><td>");
			html.append(dptr->name);
			html.append("</td><td>");
			html.append(dptr->info->GetHtmlDisplay(g, v));
			html.append("</td></tr>\n");
			
			v += 1;
		}
			
		// finish it off
		html.append("\t\t</table></div>\n\t</div>");		
		g += 1;
	}

	// and add a javascript portion that allows us
	// to store the 'current value'
	html.append("\n\n\t<script type=\"text/javascript\"><!--\n\tvar current_instance = ");
	html.append(m_current_instance);
	html.append(";\n\t//--></script>");

	return html;
}

// should only be called by a locked function
std::string WebDMA_Pimpl::get_json()
{
	// generate the values for this thing
	std::string json = "{ \"instance\": \"" + m_current_instance + "\"";

	size_t g = 0;
	
	foreach( const DataProxyGroupPtr &gptr  , m_groups )
	{	
		size_t v = 0;
		
		foreach( const DataProxyVariablePtr &dptr, gptr->variables )
		{
			json.append(", ");
			json.append(dptr->info->GetJson(g, v));
			v += 1;
		}

		g += 1;
	}

	json.append(" }");
	
	return json;
}

/**
	\brief Parses a post data string and processes a request
*/
std::string WebDMA_Pimpl::ProcessRequest(const std::string &post_data)
{
	if (post_data == "getupdate=true")
		return get_json();

	size_t group = 0, variable = 0;
	int found_flags = 0;
	std::string value;

	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	// parse the POST request into name/value pairs
	boost::char_separator<char> sep("&");
	tokenizer tokens(post_data, sep);

	foreach (const std::string &token, tokens)
	{
		size_t pos = token.find('=');
		if (pos == std::string::npos || pos > token.size()-2)
			return JSON_STATUS("INVALID");

		// we have a key/value pair now.. 
		std::string key = token.substr(0, pos); 
		std::string val = token.substr(pos+1);

		try
		{
			if (key == "group")
			{
				found_flags |= 0x01;
				group = boost::lexical_cast<size_t>(val);
			}
			else if (key == "var")
			{
				found_flags |= 0x02;
				variable = boost::lexical_cast<size_t>(val);
			}
			else if (key == "value")
			{
				found_flags |= 0x04;
				value = val;
			}
			else if (key == "instance")
			{
				found_flags |= 0x08;

				if (val != m_current_instance)
					return JSON_STATUS( "RELOAD" );
			}
		}
		catch (boost::bad_lexical_cast &)
		{
			return JSON_STATUS( "INVALID" );
		}
	}

	if (found_flags != 0x0F)
		return JSON_STATUS( "INVALID" );
	
	// ok, if everything is good so modify the proxy
	{
		lock_guard lock(m_mutex);
	
		if (m_groups.size() < group ||
			m_groups[group]->variables.size() < variable ||
			!m_groups[group]->variables[variable]->info->SetValue(value))
		{
			return JSON_STATUS( "FAIL" );
		}
	}

	return JSON_STATUS( "OK" );
}

/**
	@note This function will assume ownership of the proxy object
*/	
void WebDMA_Pimpl::InitProxy(
	DataProxyInfo * proxy, 
	const std::string &groupName, 
	const std::string &name)
{
	lock_guard lock(m_mutex);

	DataProxyGroupPtr ptr;
	
	// small data sets, linear search is ok
	foreach ( DataProxyGroupPtr &group, m_groups)
		if (group->name == groupName)
		{
			ptr = group;
			break;
		}
		
	if (ptr.get() == NULL)
	{
		ptr.reset( new DataProxyGroup() );
		ptr->name = groupName;
		m_groups.push_back(ptr);
	}
	
	DataProxyVariablePtr dptr;
	
	foreach( DataProxyVariablePtr &variable, ptr->variables)
		if (variable->name == name)
		{
			dptr = variable;
			break;
		}
	
	if (dptr.get() == NULL)
	{
		dptr.reset( new DataProxyVariable());
		dptr->name = name;
		dptr->info.reset( proxy );
		ptr->variables.push_back( dptr );
	}
	else
	{
		assert(0 && "key/value pair already registered!");
	}
	
	// tell the client theres something new its missing
	m_current_instance = boost::lexical_cast<std::string>(time(NULL));
}



