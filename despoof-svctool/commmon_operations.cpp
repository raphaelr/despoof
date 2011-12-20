#include <despoof/win32/error.h>
#include "operations.h"

using namespace despoof;

SC_HANDLE despoof::sc_manager(DWORD access)
{
	auto result = OpenSCManager(NULL, NULL, access);
	if(!result) {
		throw_windows_error("OpenSCManager");
	}
	return result;
}
