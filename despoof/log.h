#pragma once

#include <boost/format.hpp>
#include <despoof/import.h>
#include <despoof/loglevels.h>

namespace despoof { namespace log {
	extern log_function logger;

	void info(const boost::format &format);
}}
