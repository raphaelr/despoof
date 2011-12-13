#pragma once

#include <list>
#include <memory>
#include <despoof/network_interface.h>

namespace despoof {
	typedef std::list<std::shared_ptr<network_interface>> interface_container;
	typedef interface_container(*collect_function)();
	typedef collect_function(*getcollect_function)();
}
