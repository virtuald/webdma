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

#define WEBDMA_WEBDMA_CPP

#include <WebDMA/WebDMA.h>
#include "WebDMA_Pimpl.h"


WebDMA::WebDMA(
	const std::string &port, 
	const std::string &rootdir,
	const std::string &interface
) :
	m_pimpl( new WebDMA_Pimpl(port, rootdir, interface) )
{
	webdma_instance = this;
}


WebDMA::~WebDMA()
{
	delete m_pimpl;
	m_pimpl = NULL;
	
	if (webdma_instance == this)
		webdma_instance = NULL;
}


bool WebDMA::Enable()
{
	return m_pimpl->Enable();
}

bool WebDMA::Disable()
{
	return m_pimpl->Disable();
}


/*** proxy creation routines ***/


IntProxyInitializer WebDMA::CreateIntProxy( 
	const char * groupName, 
	const char * name, 
	const IntProxyFlags &flags)
{
	IntProxyInfo * proxy = new IntProxyInfo(flags);
	m_pimpl->InitProxy( proxy, groupName, name );
	return proxy->GetProxy();
}
	
FloatProxyInitializer WebDMA::CreateFloatProxy( 
	const char * groupName, 
	const char * name, 
	const FloatProxyFlags &flags)
{
	FloatProxyInfo * proxy = new FloatProxyInfo(flags);
	m_pimpl->InitProxy( proxy, groupName, name );
	return proxy->GetProxy();
}

DoubleProxyInitializer WebDMA::CreateDoubleProxy( 
	const char * groupName, 
	const char * name, 
	const DoubleProxyFlags &flags)
{
	DoubleProxyInfo * proxy = new DoubleProxyInfo(flags);
	m_pimpl->InitProxy( proxy, groupName, name );
	return proxy->GetProxy();
}


BoolProxyInitializer WebDMA::CreateBoolProxy( 
	const char * groupName, 
	const char * name, 
	const BoolProxyFlags &flags )
{
	BoolProxyInfo * proxy = new BoolProxyInfo( flags );
	m_pimpl->InitProxy( proxy, groupName, name );
	return proxy->GetProxy();
}


