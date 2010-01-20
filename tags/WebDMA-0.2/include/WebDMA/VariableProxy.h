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

#ifndef WI_VARIABLEPROXY_H
#define WI_VARIABLEPROXY_H

namespace boost {
	class shared_mutex;
};


/* 
	Each proxy provides the following operations:

	Get Operations:
	- Implicit conversion to the proxied type
	- Explicit retrieval of the proxied value (via Get())

	Set Operations:
	- Assignment of the proxied type to the proxy (via operator=)
	- Explicit setting of the proxied value (via Set())

	Some notes:

	The proxy types allows you to use it in read-only operations exactly like
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


#define IMPLEMENT_PROXY( implname, T ) 						\
															\
struct implname {											\
															\
	typedef boost::shared_mutex mutex_type;					\
															\
	implname();												\
	implname(T * proxied_value, mutex_type * mutex);		\
	operator T() const;										\
	T Get() const;											\
	implname& operator=(const T& value);					\
	void Set(const T& value);								\
															\
private:													\
	T * 					m_proxied_value;				\
	mutable mutex_type *	m_mutex;						\
};

/* 
	Defined proxy types
*/

IMPLEMENT_PROXY( IntProxy, int )
IMPLEMENT_PROXY( FloatProxy, float )
IMPLEMENT_PROXY( DoubleProxy, double )
IMPLEMENT_PROXY( BoolProxy, bool )

#undef IMPLEMENT


#endif
