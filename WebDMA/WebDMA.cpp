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


#include "WebDMA.h"
#include "WebDMA_Pimpl.h"


// default constructor -- private, never created
WebDMA::WebDMA() 
{}


void WebDMA::Enable(const std::string &port, const std::string &rootdir)
{
	WebDMA_Pimpl::GetInstance()->Enable(port, rootdir);
}



/*** proxy creation routines ***/


IntProxy WebDMA::CreateIntProxy( 
	const char * groupName, 
	const char * name, 
	const IntProxyFlags &flags)
{
	IntProxyInfo * proxy = new IntProxyInfo(flags);
	WebDMA_Pimpl::GetInstance()->InitProxy( proxy, groupName, name );
	return proxy->GetProxy();
}
	
FloatProxy WebDMA::CreateFloatProxy( 
	const char * groupName, 
	const char * name, 
	const FloatProxyFlags &flags)
{
	FloatProxyInfo * proxy = new FloatProxyInfo(flags);
	WebDMA_Pimpl::GetInstance()->InitProxy( proxy, groupName, name );
	return proxy->GetProxy();
}

DoubleProxy WebDMA::CreateDoubleProxy( 
	const char * groupName, 
	const char * name, 
	const DoubleProxyFlags &flags)
{
	DoubleProxyInfo * proxy = new DoubleProxyInfo(flags);
	WebDMA_Pimpl::GetInstance()->InitProxy( proxy, groupName, name );
	return proxy->GetProxy();
}


BoolProxy WebDMA::CreateBoolProxy( 
	const char * groupName, 
	const char * name, 
	bool default_value)
{
	BoolProxyInfo * proxy = new BoolProxyInfo(default_value);
	WebDMA_Pimpl::GetInstance()->InitProxy( proxy, groupName, name );
	return proxy->GetProxy();
}


