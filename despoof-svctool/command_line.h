#pragma once

#include "configuration.h"
#include <despoof/command_line.h>

namespace despoof {
	void command_line_to_configuration(configuration &config, int argc, char **argv);
}
