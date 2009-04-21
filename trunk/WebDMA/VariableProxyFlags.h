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

#ifndef WI_VARIABLEPROXYFLAGS_H
#define WI_VARIABLEPROXYFLAGS_H

	
#define FN(varname, T) 					\
	varname(T val)								\
	{											\
		varname##_ = val;						\
		fields_initialized |= varname##_flag;	\
		return *this;							\
	}


/**
	\brief numeric data flags, this is setup where you can do a nice and verbose
	initialization of the type. For example,
	
	\code
		FloatProxyFlags().default_value(.3F).minval(0).maxval(1).step(.01F)
		IntProxyFlags().default_value(3).readonly()
	\endcode
*/
template <typename T>
struct NumericProxyFlagsImpl {

	typedef NumericProxyFlagsImpl<T> this_type;
	
	enum {
		precision_flag = 0x00,		// yes, this is intentional
		default_value_flag = 0x01,
		minval_flag = 0x02,
		maxval_flag = 0x04,
		step_flag = 0x08,
		initialized = default_value_flag | minval_flag | maxval_flag | step_flag
	};

	T 		default_value_;
	T		minval_;
	T		maxval_;
	T		step_;
	int		precision_;
	bool	readonly_;

	// various setters for the flags
	this_type& FN(default_value, T)
	this_type& FN(minval, T)
	this_type& FN(maxval, T)
	this_type& FN(step, T)
	this_type& FN(precision, int)
	
	this_type& readonly()
	{
		readonly_ = true;
		return *this;
	}
	
	NumericProxyFlagsImpl();
	
	bool is_initialized() const 
	{
		return readonly || fields_initialized == initialized;
	}
		
private:
	int fields_initialized;
};

// integer specialization
template <>
inline
NumericProxyFlagsImpl<int>::NumericProxyFlagsImpl() :
	precision_(0),
	readonly_(false),
	fields_initialized(0)
{}

// float specialization
template <>
inline
NumericProxyFlagsImpl<float>::NumericProxyFlagsImpl() :
	precision_(2),
	readonly_(false),
	fields_initialized(0)
{}

// double specialization
template <>
inline
NumericProxyFlagsImpl<double>::NumericProxyFlagsImpl() :
	precision_(2),
	readonly_(false),
	fields_initialized(0)
{}


/// definition for integers
typedef NumericProxyFlagsImpl<int>		IntProxyFlags;

/// definition for floats
typedef NumericProxyFlagsImpl<float>	FloatProxyFlags;

/// definition for floats
typedef NumericProxyFlagsImpl<double>	DoubleProxyFlags;


#undef FN

#endif
