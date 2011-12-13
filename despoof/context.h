#pragma once

#include <list>
#include <despoof/import/collect.h>
#include <despoof/logger.h>
#include "configuration.h"
#include "adapter_address.h"

namespace despoof {
	class context {
		logger log_;
		collect_function collect_;
		configuration config_;
	public:
		context(configuration &config, collect_function collect, log_function log);

		configuration& config();
		logger& log();
		std::list<adapter_address> reload();
	};
}
