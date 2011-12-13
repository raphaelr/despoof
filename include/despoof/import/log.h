#pragma once

#include <string>

namespace despoof {
	typedef void(*log_function)(int severity, const std::string &text);
	typedef log_function(*getlog_function)();
}
