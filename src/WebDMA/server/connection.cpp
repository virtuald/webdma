//
// connection.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Modified (c) 2009 Dustin Spicuzza <dustin@virtualroadside.com>
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "connection.hpp"
#include <vector>
#include <boost/bind.hpp>
#include <boost/date_time.hpp>
#include "connection_manager.hpp"
#include "request_handler.hpp"

namespace http {
namespace server {

connection::connection(boost::asio::io_service& io_service,
		connection_manager& manager, request_handler& handler)
	: 	socket_(io_service),
		io_timeout_(io_service),
		connection_manager_(manager),
		request_handler_(handler),
		buffer_start_ptr_(0),
		buffer_end_ptr_(0)
{}

connection::~connection()
{}

boost::asio::ip::tcp::socket& connection::socket()
{
	return socket_;
}

void connection::start()
{
	request_parser_.reset();
	request_ = request();
	
	// if there is data left in the buffer
	if (buffer_start_ptr_ != buffer_end_ptr_)
	{
		parse_input_data();
	}
	else
	{
		socket_.async_read_some(boost::asio::buffer(buffer_),
			boost::bind(&connection::handle_read, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
				
		set_io_timeout();
	}
}

void connection::set_io_timeout()
{
	// default timeout is 30 seconds
	io_timeout_.expires_from_now(boost::posix_time::seconds(30));
	io_timeout_.async_wait(
			boost::bind(&connection::handle_io_timeout, shared_from_this(),
				boost::asio::placeholders::error));
}

void connection::stop()
{
	io_timeout_.cancel();
	socket_.close();
}

void connection::handle_read(const boost::system::error_code& e,
		std::size_t bytes_transferred)
{
	io_timeout_.cancel();

	if (!e)
	{	
		// set the buffer parameters
		buffer_start_ptr_ = 0;
		buffer_end_ptr_ = bytes_transferred;
		
		parse_input_data();
	}
	else if (e != boost::asio::error::operation_aborted)
	{
		connection_manager_.stop(shared_from_this());
	}
}

void connection::parse_input_data()
{
	boost::shared_ptr<reply> the_reply;
	request_parser::ParserResult result;
	input_buffer::iterator next;
	boost::tie(result, next) = request_parser_.parse(request_, 
		buffer_.data() + buffer_start_ptr_, 
		buffer_.data() + buffer_end_ptr_);
		
	// move the buffer pointer
	buffer_start_ptr_ = next - buffer_.data();

	switch (result)
	{
		case request_parser::Success:
			// successful
			the_reply.reset(new reply);
			request_handler_.handle_request(request_, *the_reply);
			boost::asio::async_write(socket_, the_reply->to_buffers(),
					boost::bind(&connection::handle_write, shared_from_this(),
						boost::asio::placeholders::error, the_reply));
			break;
		
		case request_parser::LengthRequired:
			the_reply.reset(new reply);
			*the_reply = reply::stock_reply(reply::length_required, false);
			boost::asio::async_write(socket_, the_reply->to_buffers(),
					boost::bind(&connection::handle_write, shared_from_this(),
						boost::asio::placeholders::error, the_reply));
			break;
			
		case request_parser::BadRequest:
			the_reply.reset(new reply);
			*the_reply = reply::stock_reply(reply::bad_request, false);				
			boost::asio::async_write(socket_, the_reply->to_buffers(),
					boost::bind(&connection::handle_write, shared_from_this(),
						boost::asio::placeholders::error, the_reply));
			break;
		
		case request_parser::NeedMoreData:
		
			// read more data
			socket_.async_read_some(boost::asio::buffer(buffer_),
					boost::bind(&connection::handle_read, shared_from_this(),
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
			break;
	}
	
	// don't forget to start the timeout again
	set_io_timeout();
}


void connection::handle_write(const boost::system::error_code& e, const boost::shared_ptr<reply> &the_reply)
{
	bool do_abort = true;
	io_timeout_.cancel();

	if (!e)
	{
		if (!the_reply->persistent)
		{
			// Initiate graceful connection closure if not persistent
			boost::system::error_code ignored_ec;
			socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);

		}
		else
		{
			// otherwise interpret the next request
			start();
			do_abort = false;
		}
	}

	if (e != boost::asio::error::operation_aborted && do_abort)
	{
		connection_manager_.stop(shared_from_this());
	}
}

void connection::handle_io_timeout(const boost::system::error_code &e)
{
	if (e != boost::asio::error::operation_aborted)
		connection_manager_.stop(shared_from_this());
}

} // namespace server
} // namespace http
