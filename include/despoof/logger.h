#pragma once

#include <boost/format.hpp>
#include <despoof/import.h>
#include <despoof/loglevels.h>

#define DESPOOF_LOGGER_FUNC(t) void t (const boost::format &format) { \
	log(log_##t , format.str()); }

namespace despoof {
	class logger {
		log_function log;
	public:
		logger(log_function log) : log(log) { }

		DESPOOF_LOGGER_FUNC(info)
		DESPOOF_LOGGER_FUNC(warn)
	};
}
