#pragma once

#include <despoof/win32/targetwindows.h>
#include <IPHlpApi.h>
#include <despoof/network_interface.h>

namespace despoof { namespace win32 {
	class common_network_interface : public despoof::network_interface {
		std::string name_;
		address_container addresses_, gateways_;
	public:
		common_network_interface(const IP_ADAPTER_INFO *adapter);

		virtual const std::string& name() const override { return name_; }
		virtual const address_container& addresses() const override { return addresses_; }
		virtual const address_container& gateways() const override { return gateways_; }
	};
}}
