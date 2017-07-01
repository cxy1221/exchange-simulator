#include <array>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "process_server.h"
using boost::asio::ip::tcp;

int main()
{
	boost::asio::io_service io_service;
	tcp::acceptor acc(io_service, tcp::endpoint(tcp::v6(), 9876));

	while (1) {
		boost::system::error_code ignored;

		tcp::socket socket(io_service);
		acc.accept(socket);

		std::array<char, 256> input_buffer;
		std::size_t input_size = socket.read_some(
			boost::asio::buffer(input_buffer),
			ignored);
		std::string client_msg(input_buffer.data(),				//get the message from the client
			input_buffer.data() + input_size);
		cout << client_msg;
		string msg_back_to_client = process_client_msg(client_msg);		//process the received message 
		boost::asio::write(socket, boost::asio::buffer(msg_back_to_client), ignored);		//sent the processed message back to the client 
		socket.shutdown(tcp::socket::shutdown_both, ignored);
		socket.close();
	}
	return 0;
}

