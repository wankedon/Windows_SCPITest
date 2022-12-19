#pragma once
#include <boost/asio.hpp>  
#include <string>

namespace SCPI
{
	std::string localEndpoint(const boost::asio::ip::tcp::socket& socket)
	{
		auto endpoint = socket.local_endpoint();
		return endpoint.address().to_string() + ":" + std::to_string(endpoint.port());
	}

	std::string remoteEndpoint(const boost::asio::ip::tcp::socket& socket)
	{
		auto endpoint = socket.remote_endpoint();
		return endpoint.address().to_string() + ":" + std::to_string(endpoint.port());
	}
}