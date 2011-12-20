#pragma once

#include <despoof/network_interface.h>

namespace despoof {
	struct network_api {
		typedef std::list<std::shared_ptr<network_interface>> interface_container;

		virtual interface_container collect_interfaces() = 0;
		virtual bool invalid() = 0;
		virtual void wait_until_invalid() = 0;
	};
}
