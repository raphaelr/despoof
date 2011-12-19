#pragma once

#include <list>
#include <memory>
#include <despoof/network_api.h>

namespace despoof {
	typedef network_api* (*getapi_function)();
}
