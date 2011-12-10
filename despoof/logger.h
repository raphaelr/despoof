#pragma once

#include <boost/format.hpp>
#include <despoof/import.h>

namespace despoof {
	class logger {
		log_function log;
	public:
		logger(log_function log);

		void info(const boost::format &format);
	};
}
