#include <array>
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <string>
#include "process_client.h"

using boost::asio::ip::tcp;
int main(int argc, char* argv[])
{
	boost::asio::io_service io_service;
	tcp::resolver resolver(io_service);
	tcp::resolver::query query("fe80::e47b:58ef:87c3:9b11%15", "9876");
	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	tcp::socket socket(io_service);
	boost::asio::connect(socket, endpoint_iterator);
	boost::system::error_code error;

	std::string msg;
	std::cin >> msg;
	
	boost::asio::write(socket, boost::asio::buffer(msg), error);		//send the message to the server

	std::array<char, 256> input_buffer;
	std::size_t rsize = socket.read_some(
		boost::asio::buffer(input_buffer), error);
	std::cout << std::string(input_buffer.data(), input_buffer.data() + rsize) << std::endl;		//get the message sent back from the server
	system("pause");
	return 0;
}
