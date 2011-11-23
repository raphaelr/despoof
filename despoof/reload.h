#pragma once

#include <despoof/import.h>

namespace despoof {
	extern collect_function collect;

	struct adapter_address {
		std::shared_ptr<network_interface> interface;
		boost::asio::ip::address_v4 address;
		boost::asio::ip::address_v4 gateway;

		adapter_address(std::shared_ptr<network_interface> interface, const boost::asio::ip::address_v4 &address, const boost::asio::ip::address_v4 &gateway)
			: interface(interface), address(address), gateway(gateway)
		{
		}
	};

	std::list<adapter_address> reload();
}
