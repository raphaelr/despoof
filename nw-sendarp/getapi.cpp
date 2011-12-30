
#include <despoof/win32/targetwindows.h>
#include <despoof/import/collect.h>
#include <despoof/common-nw/common_network_api.h>
#include "network_interface_implementation.h"

using namespace despoof;
using namespace despoof::win32;

extern "C" network_api __declspec(dllexport) *getapi(void)
{
	return new common_network_api<network_interface_implementation>();
}
