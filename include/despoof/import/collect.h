#pragma once

#include <list>
#include <memory>
#include <despoof/network_api.h>

namespace despoof {
	typedef std::unique_ptr<network_api>(*getapi_function)();
}
