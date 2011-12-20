#pragma once

#include <despoof/network_api.h>

namespace despoof { namespace win32 {
	class network_api_implementation : public network_api {
		HANDLE notify_wait_handle;
		OVERLAPPED notify_overlapped;

		void register_notify();
	public:
		network_api_implementation();

		virtual interface_container collect_interfaces() override;
		virtual bool invalid() override;
		virtual void wait_until_invalid() override;
	};
}}
