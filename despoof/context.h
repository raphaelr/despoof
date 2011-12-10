#pragma once

#include <list>
#include "logger.h"
#include "adapter_address.h"

namespace despoof {
	class context {
		logger log_;
		collect_function collect_;
	public:
		context(collect_function collect, log_function log);

		logger& log();
		std::list<adapter_address> reload();
	};
}
