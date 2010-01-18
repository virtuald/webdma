//
// request_handler.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Modified (c) 2009 Dustin Spicuzza <dustin@virtualroadside.com>
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "request_handler.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string/replace.hpp>
#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"

#include "../WebDMA_Pimpl.h"

namespace http {
namespace server {

request_handler::request_handler(const std::string& doc_root)
	: doc_root_(doc_root)
{
}

void request_handler::handle_request(const request& req, reply& rep)
{
	bool prefers_persistent = true;

	if (req.method != "GET" && req.method != "POST")
	{
		rep = reply::stock_reply(reply::not_implemented, prefers_persistent);
		return;
	}

	// Decode url to path.
	std::string request_path;
	if (!url_decode(req.uri, request_path))
	{
		rep = reply::stock_reply(reply::bad_request, prefers_persistent);
		return;
	}

	// Request path must be absolute and not contain "..".
	if (request_path.empty() || request_path[0] != '/'
			|| request_path.find("..") != std::string::npos)
	{
		rep = reply::stock_reply(reply::bad_request, prefers_persistent);
		return;
	}
	
	// determine if the Connection header is present 
	BOOST_FOREACH( const header &hdr, req.headers )
	{
		if (hdr.name == "Connection")
		{
			if (hdr.value == "close")
				prefers_persistent = false;
		}
	}
	

	// If path ends in slash (i.e. is a directory) then add "index.html".
	if (request_path[request_path.size() - 1] == '/')
	{
		request_path += "index.html";
	}

	if (req.method == "GET")
		handle_get_request(request_path, rep);
	else
	{
		std::string post_data;
		if (url_decode(req.post_content, post_data))
			handle_post_request(request_path, post_data, rep);
		else
			rep = reply::stock_reply(reply::bad_request, prefers_persistent);

	}
		
	// finish setting up the reply
	rep.persistent = prefers_persistent;
}


void request_handler::handle_get_request(const std::string &request_path, reply &rep)
{
	// Determine the file extension.
	std::size_t last_slash_pos = request_path.find_last_of("/");
	std::size_t last_dot_pos = request_path.find_last_of(".");
	std::string extension;
	if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
	{
		extension = request_path.substr(last_dot_pos + 1);
	}

	// Open the file to send back.
	std::string full_path = doc_root_ + request_path;
	std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
	if (!is)
	{
		rep = reply::stock_reply(reply::not_found, true);
		return;
	}

	// Fill out the reply to be sent to the client.
	rep.status = reply::ok;
	char buf[512];
	while (is.read(buf, sizeof(buf)).gcount() > 0)
		rep.content.append(buf, is.gcount());

	rep.headers.resize(1);
	rep.headers[0].name = "Content-Type";
	rep.headers[0].value = mime_types::extension_to_type(extension);
	
	if (request_path == "/index.html")
	{
		// substitute the inner html element with our custom one
		boost::replace_first(rep.content, "<!-- variables fill in here -->", WebDMA_Pimpl::GetInstance()->get_html());
	}
}

// this is intended for AJAX requests only, so it doesn't return anything
// but machine data to the user
void request_handler::handle_post_request(const std::string &request_path, const std::string &post_data, reply &rep)
{
	if (request_path != "/varcontrol")
	{
		rep = reply::stock_reply(reply::not_found, true);
		return;
	}
	
	// setup a 200 OK message
	rep = reply::stock_reply(reply::ok, true);
	
	rep.content = WebDMA_Pimpl::GetInstance()->ProcessRequest(post_data);
}


bool request_handler::url_decode(const std::string& in, std::string& out)
{
	out.clear();
	out.reserve(in.size());
	for (std::size_t i = 0; i < in.size(); ++i)
	{
		if (in[i] == '%')
		{
			if (i + 3 <= in.size())
			{
				int value;
				std::istringstream is(in.substr(i + 1, 2));
				if (is >> std::hex >> value)
				{
					out += static_cast<char>(value);
					i += 2;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else if (in[i] == '+')
		{
			out += ' ';
		}
		else
		{
			out += in[i];
		}
	}
	return true;
}

} // namespace server
} // namespace http
