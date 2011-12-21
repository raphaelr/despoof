#pragma once

#include <boost/format.hpp>
#include <despoof/import/log.h>
#include <despoof/loglevels.h>

#define DESPOOF_LOGGERFN(name) \
	void name (const std::string &str) const { \
		log(log_##name , str); \
	} \
	void name (const boost::format &format) const { \
		log(log_##name , format.str()); \
	}

namespace despoof {
	class logger {
		log_function log;
	public:
		logger(log_function log) : log(log) { }

		DESPOOF_LOGGERFN(info)
		DESPOOF_LOGGERFN(warn)
		DESPOOF_LOGGERFN(fail)
	};
}

#undef DESPOOF_LOGGERFN
