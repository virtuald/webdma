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

#ifndef WEBDMA_WEBDMA_H
#define WEBDMA_WEBDMA_H

#include <string>

#include "VariableProxy.h"
#include "VariableProxyFlags.h"

class WebDMA_Pimpl;


#ifdef _WRS_KERNEL

	// sensible defaults for FRC teams if you use the installer
	#define DEFAULT_WEBDMA_PORT 		"80"
	#define DEFAULT_WEBDMA_ROOTDIR 		"/www"
	#define DEFAULT_WEBDMA_INTERFACE 	"0.0.0.0"
	
#else

	// otherwise use these defaults
	#define DEFAULT_WEBDMA_PORT 		"8080"
	#define DEFAULT_WEBDMA_ROOTDIR 		"www"
	#define DEFAULT_WEBDMA_INTERFACE 	"127.0.0.1"
	
#endif



/**
	\class WebDMA
	\brief Singleton class used to allow users to remotely modify variables
	via a webserver launched in a seperate task.
	
	@todo Make values persistent, by writing to file?
*/
class WebDMA {
public:

	/**
		Default constructor, specify the port/root directory
		of the server here. Yes, port is a string. 
		
		The server is not enabled by default, you must call Enable()
		
		@param port			Port that the webserver should listen on
		@param rootdir		Root directory of the webserver
		@param interface	Address of network interface that WebDMA should 
							listen on
	*/
	WebDMA(
		const std::string &port = DEFAULT_WEBDMA_PORT, 
		const std::string &rootdir = DEFAULT_WEBDMA_ROOTDIR,
		const std::string &interface = DEFAULT_WEBDMA_INTERFACE
	);
	
	
	~WebDMA();
	
	/**
		You should call this to start the web server. You may add more
		proxies after this is called.
	*/
	bool Enable();	
	
	/**
		Optional call to disable the web server. Does NOT clear existing proxies.
		
		@param seconds 		Number of seconds to wait for the WebDMA thread 
							to exit before giving up
	*/
	bool Disable();	
	

	/** 
		Use this to initialize an integer proxy
		
		@param groupName	group this variable belongs to
		@param name			name of this variable (should be unique)
		@param flags		Use this to set min/max/default values and etc. For example,
							IntProxyFlags().default_value(x).minval(x).maxval(x).step(x)
	*/
	IntProxy CreateIntProxy( const char * groupName, const char * name, const IntProxyFlags &flags);
	

	/** 
		Use this to initialize a floating point proxy
		
		@param groupName	group this variable belongs to
		@param name			name of this variable (should be unique)
		@param flags		Use this to set min/max/default values and etc. For example,
							FloatProxyFlags().default_value(x).minval(x).maxval(x).step(x).precision(2)
	*/
	FloatProxy CreateFloatProxy( const char * groupName, const char * name, const FloatProxyFlags &flags);
	
	/** 
		Use this to initialize a 'double' floating point proxy
		
		@param groupName	group this variable belongs to
		@param name			name of this variable (should be unique)
		@param flags		Use this to set min/max/default values and etc. For example,
							DoubleProxyFlags().default_value(x).minval(x).maxval(x).step(x).precision(2)
	*/
	DoubleProxy CreateDoubleProxy( const char * groupName, const char * name, const DoubleProxyFlags &flags);
	
	
	/**
		Use this to initialize a boolean proxy
		
		@param groupName		group this variable belongs to
		@param name				name of this variable (should be unique)
		@param default_value 	the starting value of this proxy
	*/
	BoolProxy CreateBoolProxy( const char * groupName, const char * name, bool default_value);
	

	/// @todo other types of variables: enums, doubles, signed/unsigned.. 
	
private:
	
	// no copying/assigning
	WebDMA(const WebDMA&);
	WebDMA& operator=(const WebDMA&);
	
	WebDMA_Pimpl * m_pimpl;
};

/*
	This is here for convenience for quick debugging, so you 
	don't have to keep passing a WebDMA instance around.
	
	HOWEVER: If you are implementing tuning, then you should
	probably pass a WebDMA instance around. This is only really
	intended for debugging use. 
*/
#ifdef WEBDMA_WEBDMA_CPP
	WebDMA * webdma_instance;
#else
	extern WebDMA * webdma_instance;
#endif



#endif
