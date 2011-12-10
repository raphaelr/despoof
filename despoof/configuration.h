#pragma once

#include <stdexcept>

namespace despoof {
	struct configuration {
		configuration();

		// Internal value; If true, despoof does not start, for example because
		// the --help command line option was specified
		bool _nostart;

		int interval;
	};
}
