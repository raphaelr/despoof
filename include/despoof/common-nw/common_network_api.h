#pragma once

#include <despoof/win32/targetwindows.h>
#include <despoof/win32/error.h>
#include <despoof/network_api.h>
#include <vector>

namespace despoof { namespace win32 {
	template<class interface_implementation>
	class common_network_api : public network_api {
		HANDLE notify_wait_handle;
		OVERLAPPED notify_overlapped;

		void register_notify();
	public:
		common_network_api();

		virtual interface_container collect_interfaces() override;
		virtual bool invalid() override;
		virtual void wait_until_invalid(abortable &ab) override;
	};

	template<class T>
	inline common_network_api<T>::common_network_api()
	{
		notify_overlapped.hEvent = CreateEvent(nullptr, true, false, nullptr);
		if(!notify_overlapped.hEvent) {
			throw_windows_error("CreateEvent");
		}
		register_notify();
	}

	template<class T>
	inline void common_network_api<T>::register_notify()
	{
		if(!ResetEvent(notify_overlapped.hEvent)) {
			throw_windows_error("ResetEvent");
		}

		DWORD error = NotifyAddrChange(&notify_wait_handle, &notify_overlapped);
		if(error != ERROR_IO_PENDING) {
			throw_windows_error2("NotifyAddrChange", error);
		}
	}

	template<class T>
	inline bool common_network_api<T>::invalid()
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
		return true; // Satisfy compiler
	}

	template<class T>
	inline void common_network_api<T>::wait_until_invalid(abortable &ab)
	{
		HANDLE handles[] = {notify_wait_handle, ab.wait_event()};
		auto result = WaitForMultipleObjects(2, handles, false, INFINITE);

		switch(result) {
		case WAIT_OBJECT_0:
			register_notify();
		case WAIT_OBJECT_0 + 1:
			break;
		case WAIT_FAILED:
			throw_windows_error("WaitForSingleObject");
		default:
			assert(!"WaitForSingleObject didn't return WAIT_OBJECT_0/1 or WAIT_FAILED");
		}
	}

	template<class interface_implementation>
	inline network_api::interface_container common_network_api<interface_implementation>::collect_interfaces()
	{
		interface_container result;
		std::vector<uint8_t> buffer;
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
			result.push_back(std::make_shared<interface_implementation>(adapter));
		}
		return result;
	}
}}
