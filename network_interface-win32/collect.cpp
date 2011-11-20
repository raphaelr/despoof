#include <cstdint>
#include <vector>
#include <despoof/win32/error.h>
#include "network_interface_implementation.h"

using namespace std;
using namespace despoof;
using namespace despoof::win32;

network_interface::interface_container network_interface::collect()
{
	network_interface::interface_container result;
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
			throw_windows_error2(L"GetAdaptersInfo", error);
		}
	} while(error != ERROR_SUCCESS);

	for(auto adapter = info; adapter; adapter = adapter->Next) {
		result.push_back(unique_ptr<network_interface_implementation>(new network_interface_implementation(adapter)));
	}
	return result;
}
