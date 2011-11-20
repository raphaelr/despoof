#pragma once

#include <memory>
#include <list>
#include <boost/asio/ip/address_v4.hpp>
#include <despoof/reference_type.h>

namespace despoof {
	struct network_interface : private reference_type {
		typedef std::list<boost::asio::ip::address_v4> address_container;
		typedef std::list<std::unique_ptr<network_interface>> interface_container;

		virtual const address_container& addresses() const = 0;
		virtual const address_container& gateways() const = 0;

		static const interface_container collect();
	};
}
