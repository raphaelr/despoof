#pragma once

#include <stdexcept>

namespace despoof {
	struct command_line_error : std::runtime_error {
		command_line_error() : std::runtime_error("Cannot parse command line") { }
		virtual ~command_line_error() { }

		virtual void print_errors() const = 0;
	};
}
