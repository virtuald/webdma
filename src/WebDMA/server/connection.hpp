//
// connection.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Modified (c) 2009 Dustin Spicuzza <dustin@virtualroadside.com>
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_CONNECTION_HPP
#define HTTP_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "reply.hpp"
#include "request.hpp"
#include "request_handler.hpp"
#include "request_parser.hpp"

namespace http {
namespace server {

class connection_manager;

/// Represents a single connection from a client.
class connection
	: public boost::enable_shared_from_this<connection>,
		private boost::noncopyable
{
	typedef boost::array<char, 8192> input_buffer;

public:
	/// Construct a connection with the given io_service.
	explicit connection(boost::asio::io_service& io_service,
			connection_manager& manager, request_handler& handler);

	~connection();

	/// Get the socket associated with the connection.
	boost::asio::ip::tcp::socket& socket();

	/// Start the first asynchronous operation for the connection.
	void start();

	/// Stop all asynchronous operations associated with the connection.
	void stop();

private:
	/// Starts the io timeout routine
	void set_io_timeout();

	/// Handle completion of a read operation.
	void handle_read(const boost::system::error_code& e,
			std::size_t bytes_transferred);

	/// Handle completion of a write operation.
	void handle_write(const boost::system::error_code& e,
			const boost::shared_ptr<reply> &the_reply);
	
	/// Handle an I/O timeout
	void handle_io_timeout(const boost::system::error_code& e);

	/// parse the input
	void parse_input_data();

	/// Socket for the connection.
	boost::asio::ip::tcp::socket socket_;
	
	/// Read timeout
	boost::asio::deadline_timer io_timeout_;

	/// The manager for this connection.
	connection_manager& connection_manager_;

	/// The handler used to process the incoming request.
	request_handler& request_handler_;

	/// Buffer for incoming data.
	input_buffer buffer_;
	
	/// Buffer parameters (used by parse_input_data)
	size_t buffer_start_ptr_;
	size_t buffer_end_ptr_;

	/// The incoming request.
	request request_;

	/// The parser for the incoming request.
	request_parser request_parser_;
};

typedef boost::shared_ptr<connection> connection_ptr;

} // namespace server
} // namespace http

#endif // HTTP_CONNECTION_HPP
