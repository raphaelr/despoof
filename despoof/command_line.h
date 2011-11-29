#pragma once

#include "configuration.h"

namespace despoof {
	void command_line_to_configuration(configuration &config, int argc, char **argv);

	struct command_line_error : std::runtime_error {
		command_line_error();
		virtual ~command_line_error() { }

		virtual void print_errors() const = 0;
	};
}
