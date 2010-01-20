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




#include <WebDMA/VariableProxy.h>

#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>

typedef boost::shared_lock< boost::shared_mutex > read_lock;
typedef boost::unique_lock< boost::shared_mutex > write_lock;


#define IMPLEMENT_IMPL( implname, T ) 						\
															\
															\
implname::implname() :										\
	m_proxied_value(NULL), m_mutex(NULL)					\
{}															\
															\
implname::implname(T * proxied_value, mutex_type * mutex) :	\
	m_proxied_value(proxied_value), m_mutex(mutex)			\
{}															\
															\
implname::operator T() const								\
{															\
	read_lock lock(*m_mutex);								\
	return *m_proxied_value; 								\
}															\
															\
T implname::Get() const										\
{															\
	read_lock lock(*m_mutex);								\
	return *m_proxied_value; 								\
}															\
															\
implname& implname::operator=(const T& value)				\
{															\
	write_lock lock(*m_mutex);								\
	*m_proxied_value = value;								\
	return *this;											\
}															\
															\
void implname::Set(const T& value)							\
{															\
	write_lock lock(*m_mutex);								\
	*m_proxied_value = value;								\
}



IMPLEMENT_IMPL( IntProxy, int )
IMPLEMENT_IMPL( FloatProxy, float )
IMPLEMENT_IMPL( DoubleProxy, double )
IMPLEMENT_IMPL( BoolProxy, bool )



