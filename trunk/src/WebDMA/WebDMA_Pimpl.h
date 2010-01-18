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

#ifndef WebDMA_Pimpl_WebDMA_Pimpl_H
#define WebDMA_Pimpl_WebDMA_Pimpl_H

#include <string>
#include <vector>

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

#include "DataProxyInfo.h"

namespace http {
	namespace server {
		class request_handler;
		class server;
	}
}

/**
	\class WebDMA_Pimpl
	\brief Singleton class used to allow users to remotely modify variables
	via a webserver launched in a seperate task.
	
	@todo Make values persistent, by writing to file?
*/
class WebDMA_Pimpl {

	// various type definitions
	typedef boost::lock_guard<boost::mutex>			lock_guard;
	
	struct DataProxyVariable {
		std::string 								name;
		boost::shared_ptr<DataProxyInfo> 			info;
	};
	
	typedef boost::shared_ptr< DataProxyVariable > 	DataProxyVariablePtr;
	
	struct DataProxyGroup {
		std::string 								name;
		std::vector< DataProxyVariablePtr > 		variables;
	};
	
	typedef boost::shared_ptr< DataProxyGroup >		DataProxyGroupPtr;
	typedef std::vector< DataProxyGroupPtr >		DataProxyGroups;

	friend class http::server::request_handler;

public:
	
	// internal utility functions
	static WebDMA_Pimpl * GetInstance();

	void InitProxy(
		DataProxyInfo * proxy, 
		const std::string &groupName, 
		const std::string &name);
		
	// internal functions that start the webserver thread
	void Enable(const std::string &port, const std::string &rootdir);
	
	~WebDMA_Pimpl();

private:

	WebDMA_Pimpl();
	
	void ThreadFn();
	
	// functions used to process/generate html response
	std::string ProcessRequest(const std::string &post_data);
	
	std::string get_html();
	std::string get_json();
	
	/// port that the server will listen on
	std::string				m_port;
	
	/// root directory where webpages are found
	std::string				m_rootDir;
	
	/// each ajax request is compared against this, and if it doesn't
	/// match then it means the page must reload. This is updated each time
	/// a new proxy is added or deleted
	std::string 			m_current_instance;
	
	/// global access lock
	boost::mutex			m_mutex;
	
	/// thread
	boost::shared_ptr< boost::thread > m_thread;
	
	http::server::server *	m_server;
	
	bool 					m_thread_created;
	
	/// storage of the proxied data
	DataProxyGroups 		m_groups;
	
	
};

#endif
