#include <despoof/win32/targetwindows.h>
#include <cstdint>
#include <vector>
#include <despoof/import/collect.h>
#include <despoof/win32/error.h>
#include "network_interface_implementation.h"

using namespace std;
using namespace despoof;
using namespace despoof::win32;

static interface_container collect_implementation()
{
	interface_container result;
	vector<uint8_t> buffer;
	IP_ADAPTER_INFO *info = nullptr;
	ULONG length = 0;
	DWORD error;

	do {
		error = GetAdaptersInfo(info, &length);
		switch(error) {
		case ERROR_BUFFER_OVERFLOW:
			buffer.resize(length);
			info = (IP_ADAPTER_INFO*) &buffer[0];
			break;
		case ERROR_NO_DATA:
			return result;
		case ERROR_SUCCESS:
			break;
		default:
			throw_windows_error2("GetAdaptersInfo", error);
		}
	} while(error != ERROR_SUCCESS);

	for(auto adapter = info; adapter; adapter = adapter->Next) {
		result.push_back(make_shared<network_interface_implementation>(adapter));
	}
	return result;
}

extern "C" collect_function __declspec(dllexport) getcollect(void)
{
	return collect_implementation;
}
