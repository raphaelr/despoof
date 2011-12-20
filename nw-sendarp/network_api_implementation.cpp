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
	notify_overlapped.hEvent = CreateEvent(nullptr, true, false, nullptr);
	if(!notify_overlapped.hEvent) {
		throw_windows_error("CreateEvent");
	}
	register_notify();
}

void network_api_implementation::register_notify()
{
	if(!ResetEvent(notify_overlapped.hEvent)) {
		throw_windows_error("ResetEvent");
	}

	DWORD error = NotifyAddrChange(&notify_wait_handle, &notify_overlapped);
	if(error != ERROR_IO_PENDING) {
		throw_windows_error2("NotifyAddrChange", error);
	}
}

bool network_api_implementation::invalid()
{
	auto result = WaitForSingleObject(notify_wait_handle, 0);

	switch(result) {
	case WAIT_OBJECT_0:
		register_notify();
		return true;
	case WAIT_TIMEOUT:
		return false;
	case WAIT_FAILED:
		throw_windows_error("WaitForSingleObject");
	default:
		assert(!"WaitForSingleObject didn't return WAIT_OBJECT_0, WAIT_TIMEOUT or WAIT_FAILED");
	}
}

void network_api_implementation::wait_until_invalid(abortable &ab)
{
	again:
	ab.recognize_abort(true);
	auto result = WaitForSingleObjectEx(notify_wait_handle, INFINITE, true);
	ab.recognize_abort(false);

	switch(result) {
	case WAIT_OBJECT_0:
		register_notify();
		break;
	case WAIT_IO_COMPLETION:
		if(ab.abort_pending()) { return; }
		goto again;
	case WAIT_FAILED:
		throw_windows_error("WaitForSingleObjectEx");
	default:
		assert(!"WaitForSingleObjectEx didn't return WAIT_OBJECT_0, WAIT_IO_COMPLETION or WAIT_FAILED");
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
