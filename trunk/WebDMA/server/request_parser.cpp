//
// request_parser.cpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Modified (c) 2009 Dustin Spicuzza <dustin@virtualroadside.com>
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "request_parser.hpp"
#include "request.hpp"

#include <boost/lexical_cast.hpp>

namespace http {
namespace server {

request_parser::request_parser()
	: state_(method_start)
{
}

void request_parser::reset()
{
	state_ = method_start;
	content_received_ = 0;
	expected_content_bytes_ = 0;
}

request_parser::ParserResult request_parser::consume(request& req, char input)
{
	switch (state_)
	{
	case method_start:
		if (!is_char(input) || is_ctl(input) || is_tspecial(input))
		{
			return BadRequest;
		}
		else
		{
			state_ = method;
			req.method.push_back(input);
			return NeedMoreData;
		}
	case method:
		if (input == ' ')
		{
			state_ = uri;
			return NeedMoreData;
		}
		else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
		{
			return BadRequest;
		}
		else
		{
			req.method.push_back(input);
			return NeedMoreData;
		}
	case uri_start:
		if (is_ctl(input))
		{
			return BadRequest;
		}
		else
		{
			state_ = uri;
			req.uri.push_back(input);
			return NeedMoreData;
		}
	case uri:
		if (input == ' ')
		{
			state_ = http_version_h;
			return NeedMoreData;
		}
		else if (is_ctl(input))
		{
			return BadRequest;
		}
		else
		{
			req.uri.push_back(input);
			return NeedMoreData;
		}
	case http_version_h:
		if (input == 'H')
		{
			state_ = http_version_t_1;
			return NeedMoreData;
		}
		else
		{
			return BadRequest;
		}
	case http_version_t_1:
		if (input == 'T')
		{
			state_ = http_version_t_2;
			return NeedMoreData;
		}
		else
		{
			return BadRequest;
		}
	case http_version_t_2:
		if (input == 'T')
		{
			state_ = http_version_p;
			return NeedMoreData;
		}
		else
		{
			return BadRequest;
		}
	case http_version_p:
		if (input == 'P')
		{
			state_ = http_version_slash;
			return NeedMoreData;
		}
		else
		{
			return BadRequest;
		}
	case http_version_slash:
		if (input == '/')
		{
			req.http_version_major = 0;
			req.http_version_minor = 0;
			state_ = http_version_major_start;
			return NeedMoreData;
		}
		else
		{
			return BadRequest;
		}
	case http_version_major_start:
		if (is_digit(input))
		{
			req.http_version_major = req.http_version_major * 10 + input - '0';
			state_ = http_version_major;
			return NeedMoreData;
		}
		else
		{
			return BadRequest;
		}
	case http_version_major:
		if (input == '.')
		{
			state_ = http_version_minor_start;
			return NeedMoreData;
		}
		else if (is_digit(input))
		{
			req.http_version_major = req.http_version_major * 10 + input - '0';
			return NeedMoreData;
		}
		else
		{
			return BadRequest;
		}
	case http_version_minor_start:
		if (is_digit(input))
		{
			req.http_version_minor = req.http_version_minor * 10 + input - '0';
			state_ = http_version_minor;
			return NeedMoreData;
		}
		else
		{
			return BadRequest;
		}
	case http_version_minor:
		if (input == '\r')
		{
			state_ = expecting_newline_1;
			return NeedMoreData;
		}
		else if (is_digit(input))
		{
			req.http_version_minor = req.http_version_minor * 10 + input - '0';
			return NeedMoreData;
		}
		else
		{
			return BadRequest;
		}
	case expecting_newline_1:
		if (input == '\n')
		{
			state_ = header_line_start;
			return NeedMoreData;
		}
		else
		{
			return BadRequest;
		}
	case header_line_start:
		if (input == '\r')
		{
			state_ = expecting_newline_3;
			return NeedMoreData;
		}
		else if (!req.headers.empty() && (input == ' ' || input == '\t'))
		{
			state_ = header_lws;
			return NeedMoreData;
		}
		else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
		{
			return BadRequest;
		}
		else
		{
			req.headers.push_back(header());
			req.headers.back().name.push_back(input);
			state_ = header_name;
			return NeedMoreData;
		}
	case header_lws:
		if (input == '\r')
		{
			state_ = expecting_newline_2;
			return NeedMoreData;
		}
		else if (input == ' ' || input == '\t')
		{
			return NeedMoreData;
		}
		else if (is_ctl(input))
		{
			return BadRequest;
		}
		else
		{
			state_ = header_value;
			req.headers.back().value.push_back(input);
			return NeedMoreData;
		}
	case header_name:
		if (input == ':')
		{
			state_ = space_before_header_value;
			return NeedMoreData;
		}
		else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
		{
			return BadRequest;
		}
		else
		{
			req.headers.back().name.push_back(input);
			return NeedMoreData;
		}
	case space_before_header_value:
		if (input == ' ')
		{
			state_ = header_value;
			return NeedMoreData;
		}
		else
		{
			return BadRequest;
		}
	case header_value:
		if (input == '\r')
		{
			state_ = expecting_newline_2;
			return NeedMoreData;
		}
		else if (is_ctl(input))
		{
			return BadRequest;
		}
		else
		{
			req.headers.back().value.push_back(input);
			return NeedMoreData;
		}
	case expecting_newline_2:
		if (input == '\n')
		{
			state_ = header_line_start;
			return NeedMoreData;
		}
		else
		{
			return BadRequest;
		}
	case expecting_newline_3:
		if (input == '\n')
		{
			if (req.method != "POST")
				return Success;
				
			// check to see if we need to parse for post content
			for (size_t i = 0; i < req.headers.size(); i++)
				if (req.headers[i].name == "Content-Length")
				{
					try 
					{
						expected_content_bytes_ = boost::lexical_cast<std::size_t>(req.headers[i].value);
					}
					catch (boost::bad_lexical_cast &)
					{
						return BadRequest;
					}
					
					state_ = expecting_content;
					return NeedMoreData;
				}
			
			return LengthRequired;
		}
		else
		{
			return BadRequest;
		}
	case expecting_content:
		{
			req.post_content.push_back(input);
			if (++content_received_ == expected_content_bytes_)
				return Success;
				
			return NeedMoreData;
		}
	default:
		return BadRequest;
	}
}

bool request_parser::is_char(int c)
{
	return c >= 0 && c <= 127;
}

bool request_parser::is_ctl(int c)
{
	return (c >= 0 && c <= 31) || c == 127;
}

bool request_parser::is_tspecial(int c)
{
	switch (c)
	{
	case '(': case ')': case '<': case '>': case '@':
	case ',': case ';': case ':': case '\\': case '"':
	case '/': case '[': case ']': case '?': case '=':
	case '{': case '}': case ' ': case '\t':
		return true;
	default:
		return false;
	}
}

bool request_parser::is_digit(int c)
{
	return c >= '0' && c <= '9';
}

} // namespace server
} // namespace http
