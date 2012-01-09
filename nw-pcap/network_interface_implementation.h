#pragma once

#include <despoof/common-nw/common_network_interface.h>
#include <array>
#include <stdint.h>
#include <boost/asio/ip/address_v4.hpp>
#include <pcap/pcap.h>

namespace despoof { namespace win32 {
	class network_interface_implementation : public common_network_interface {
		typedef std::array<uint8_t, 8> mac_address;
		pcap_t *pcap;
		mac_address interface_mac;

		bool mac_for(mac_address &output, const boost::asio::ip::address_v4 &me, const boost::asio::ip::address_v4 &him, const logger &log);
	public:
		network_interface_implementation(const IP_ADAPTER_INFO *adapter, logger &log);
		~network_interface_implementation();

		virtual void fix(const boost::asio::ip::address_v4 &me, const boost::asio::ip::address_v4 &him, const logger &log) override;
	};
}}
