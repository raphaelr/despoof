#pragma once

#include <despoof/network_interface.h>
#include <string>

namespace despoof {
	typedef std::list<std::shared_ptr<network_interface>> interface_container;
	typedef interface_container(*collect_function)();
	typedef collect_function(*getcollect_function)();

	typedef void(*log_function)(int severity, const std::string &text);
	typedef log_function(*getlog_function)();
}
