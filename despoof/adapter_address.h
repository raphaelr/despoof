#pragma once

#include <boost/asio/ip/address_v4.hpp>

namespace despoof {
	struct adapter_address {
		std::shared_ptr<network_interface> interface;
		boost::asio::ip::address_v4 address;
		boost::asio::ip::address_v4 gateway;

		adapter_address(std::shared_ptr<network_interface> interface, const boost::asio::ip::address_v4 &address, const boost::asio::ip::address_v4 &gateway)
			: interface(interface), address(address), gateway(gateway)
		{
		}
	};
}
