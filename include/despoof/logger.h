#pragma once

#include <boost/format.hpp>
#include <despoof/import.h>
#include <despoof/loglevels.h>

namespace despoof {
	class logger {
		log_function log;
	public:
		logger(log_function log) : log(log) { }

		void info(const boost::format &format)
		{
			log(log_info, format.str());
		}
	};
}
