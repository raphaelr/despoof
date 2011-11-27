#pragma once

#include <list>
#include <string>
#include <boost/asio/ip/address_v4.hpp>
#include <despoof/reference_type.h>

namespace despoof {
	struct network_interface : private reference_type {
		typedef std::list<boost::asio::ip::address_v4> address_container;

		virtual const std::string& name() const = 0;
		virtual const address_container& addresses() const = 0;
		virtual const address_container& gateways() const = 0;
	};
}
