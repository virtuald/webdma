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



#ifndef STATICDELETER_H
#define STATICDELETER_H


/**
	\class StaticDeleter
	\brief Deletes a pointer when this object goes out of scope
	
	Generally, this is useful for implementation of the singleton pattern
	in some form, such as the following example:
	
	\code
	
	SomeType * SomeType::m_instance = NULL;
	StaticDeleter<SomeType> someTypeDeleter(&m_instance);
	
	SomeType * SomeType::GetInstance()
	{
		if (SomeType::m_instance == NULL)
			SomeType::m_instance = new SomeType();
		return SomeType::m_instance;
	}
	
	\endcode
	
	@warning A key assumption made by this class is that the static object
	is only accessed during the normal scope of the program -- ie, the object
	that this class contains a pointer to a pointer to should not be accessed
	by anything that could be called after main() is complete. For some code
	bases, this can be very tricky to enforce.
*/
template <typename TypeToDelete>
class StaticDeleter {
public:

	StaticDeleter(TypeToDelete ** ptr2ptr) :
		m_ptr2ptr(ptr2ptr)
	{}

	~StaticDeleter()
	{
		if (*m_ptr2ptr)
		{
			delete *m_ptr2ptr;
			*m_ptr2ptr = NULL;
		}
	}

private:
	TypeToDelete ** m_ptr2ptr;
};

#endif

