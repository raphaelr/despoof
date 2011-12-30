#pragma once

#include <despoof/common-nw/common_network_interface.h>
#include <stdint.h>
#include <pcap/pcap.h>

namespace despoof { namespace win32 {
	class network_interface_implementation : public common_network_interface {
		pcap_t *pcap;
		uint8_t mac[6];
	public:
		network_interface_implementation(const IP_ADAPTER_INFO *adapter, logger &log);
		~network_interface_implementation();

		virtual void fix(const boost::asio::ip::address_v4 &me, const boost::asio::ip::address_v4 &him, const logger &log) override;
	};
}}
