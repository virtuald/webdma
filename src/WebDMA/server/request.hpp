//
// request.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Modified (c) 2009 Dustin Spicuzza <dustin@virtualroadside.com>
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <vector>
#include "header.hpp"

namespace http {
namespace server {

/// A request received from a client.
struct request
{
	std::string method;
	std::string uri;
	int http_version_major;
	int http_version_minor;
	std::vector<header> headers;
	
	std::string post_content;
	
	// set to true if the request is persistent
	bool persistent;
};

} // namespace server
} // namespace http

#endif // HTTP_REQUEST_HPP
