#pragma once

#include <despoof/common-nw/common_network_interface.h>

namespace despoof { namespace win32 {
	class network_interface_implementation : public common_network_interface {
	public:
		network_interface_implementation(const IP_ADAPTER_INFO *adapter);

		virtual void fix(const boost::asio::ip::address_v4 &me, const boost::asio::ip::address_v4 &him, const logger &log) override;
	};
}}
