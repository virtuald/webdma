//
// mime_types.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Modified (c) 2009 Dustin Spicuzza <dustin@virtualroadside.com>
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "mime_types.hpp"
#include <boost/algorithm/string/compare.hpp>

namespace http {
namespace server {
namespace mime_types {

struct mapping
{
	const char* extension;
	const char* mime_type;
} mappings[] =
{
	{ "css", "text/css" },
	{ "gif", "image/gif" },
	{ "htm", "text/html" },
	{ "html", "text/html" },
	{ "jpg", "image/jpeg" },
	{ "js", "text/javascript" },
	{ "png", "image/png" },
	{ 0, 0 } // Marks end of list.
};

std::string extension_to_type(const std::string& extension)
{
	for (mapping* m = mappings; m->extension; ++m)
	{
		if (m->extension == extension)
		{
			return m->mime_type;
		}
	}

	return "text/plain";
}

} // namespace mime_types
} // namespace server
} // namespace http
