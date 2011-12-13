#pragma once

#include <boost/format.hpp>
#include <despoof/import/log.h>
#include <despoof/loglevels.h>

namespace despoof {
	class logger {
		log_function log;
	public:
		logger(log_function log) : log(log) { }

		void info(const boost::format &format) const
		{
			log(log_info, format.str());
		}

		void warn(const boost::format &format) const
		{
			log(log_warn, format.str());
		}
	};
}
