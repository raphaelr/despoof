#pragma once

#include "context.h"
#include "adapter_address.h"

namespace despoof {
	void iterate(context &ctx, std::list<adapter_address> &addresses);
}
