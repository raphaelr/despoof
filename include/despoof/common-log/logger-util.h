#pragma once

#include <string>
#include <ostream>

namespace despoof {
	void log(std::ostream &target, int severity, const std::string &text);
}
