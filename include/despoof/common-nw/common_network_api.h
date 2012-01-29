#pragma once

#include <despoof/win32/targetwindows.h>
#include <despoof/win32/error.h>
#include <despoof/network_api.h>
#include <vector>
#include "interface_change_listener.h"

namespace despoof { namespace win32 {
	template<class interface_implementation>
	class common_network_api : public network_api {
		std::unique_ptr<interface_change_listener> change_listener;
	public:
		common_network_api();

		virtual interface_container collect_interfaces(logger &log) override;
		virtual bool invalid() override;
		virtual void wait_until_invalid(abortable &ab) override;
	};

	template<class T>
	inline common_network_api<T>::common_network_api()
		: change_listener(interface_change_listener::create())
	{
	}

	template<class T>
	inline bool common_network_api<T>::invalid()
	{
		return change_listener->changed();
	}

	template<class T>
	inline void common_network_api<T>::wait_until_invalid(abortable &ab)
	{
		change_listener->wait(ab);
	}

	template<class interface_implementation>
	inline network_api::interface_container common_network_api<interface_implementation>::collect_interfaces(logger &log)
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
				throw_windows_error("GetAdaptersInfo", error);
			}
		} while(error != ERROR_SUCCESS);

		for(auto adapter = info; adapter; adapter = adapter->Next) {
			if(adapter->Type == MIB_IF_TYPE_ETHERNET || adapter->Type == IF_TYPE_IEEE80211) {
				result.push_back(std::make_shared<interface_implementation>(adapter, log));
			}
		}
		return result;
	}
}}
