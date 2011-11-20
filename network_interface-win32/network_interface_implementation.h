#pragma once

#include <despoof/win32/targetwindows.h>
#include <despoof/network_interface.h>

namespace despoof { namespace win32 {
	class network_interface_implementation : public despoof::network_interface {
		std::wstring name_;
		address_container addresses_, gateways_;
	public:
		network_interface_implementation(const IP_ADAPTER_INFO *adapter);

		virtual const std::wstring& name() const override { return name_; }
		virtual const address_container& addresses() const override { return addresses_; }
		virtual const address_container& gateways() const override { return gateways_; }
	};
}}
