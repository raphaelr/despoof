#include <despoof/win32/targetwindows.h>
#include <cstdint>
#include <vector>
#include <memory>
#include <despoof/import/collect.h>
#include <despoof/win32/error.h>
#include "network_interface_implementation.h"
#include "network_api_implementation.h"

using namespace std;
using namespace despoof;
using namespace despoof::win32;

network_api_implementation::network_api_implementation()
{
	register_notify();
}

void network_api_implementation::register_notify()
{
	notify_overlapped.hEvent = CreateEvent(nullptr, true, false, nullptr);
	DWORD error = NotifyAddrChange(&notify_wait_handle, &notify_overlapped);
	if(error != ERROR_IO_PENDING) {
		throw_windows_error2("NotifyAddrChange", error);
	}
}

bool network_api_implementation::invalid()
{
	DWORD uninteresting;
	if(GetOverlappedResult(notify_wait_handle, &notify_overlapped, &uninteresting, false)) {
		register_notify();
		return true;
	} else {
		auto error = GetLastError();
		if(error == ERROR_IO_INCOMPLETE) {
			return false;
		} else {
			throw_windows_error2("GetOverlappedResult", error);
		}
	}
}

network_api::interface_container network_api_implementation::collect_interfaces()
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

extern "C" network_api __declspec(dllexport) *getapi(void)
{
	return new network_api_implementation();
}
