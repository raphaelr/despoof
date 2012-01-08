#pragma once

#include <memory>
#include "context.h"

namespace despoof {
	bool init(int argc, char **argv, std::unique_ptr<despoof::context> &ctx);
}
