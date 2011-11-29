#pragma once

#include <stdexcept>

namespace despoof {
	struct configuration {
		int interval;

		static configuration load(int argc, char **argv);
	};

	struct configuration_error : std::runtime_error {
	public:
		configuration_error();
		virtual ~configuration_error() { }

		virtual void print_errors() const = 0;
	};
}
