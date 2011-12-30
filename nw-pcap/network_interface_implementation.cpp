#include "network_interface_implementation.h"
#include "pcap_exception.h"
#include <stdint.h>
#include <WinSock2.h>
#include <despoof/win32/error.h>

using boost::format;
using namespace boost::asio::ip;
using namespace despoof;
using namespace despoof::win32;

network_interface_implementation::network_interface_implementation(const IP_ADAPTER_INFO *info, logger &log)
	: common_network_interface(info)
{
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap = pcap_open_live((format("\\Device\\NPF_%1%") % info->AdapterName).str().c_str(), 0, 0, 0, errbuf);
	if(!pcap) {
		log.warn(format("Can't open pcap driver for %1% (aka %2%)") % info->Description % info->AdapterName);
	}
	memcpy(mac, info->Address, 6);
}

network_interface_implementation::~network_interface_implementation()
{
	if(pcap) {
		pcap_close(pcap);
	}
}

namespace {
#pragma pack(push)
#pragma pack(1)
	const uint16_t ethertype_arp = htons(0x806);
	const uint16_t htype_ethernet = htons(1);
	const uint16_t ptype_ipv4 = htons(0x800);
	const uint8_t hlen_ethernet = 6;
	const uint8_t plen_ipv4 = 4;
	const uint16_t operation_reply = htons(2);

	struct arp_packet {
		uint8_t eth_dst[6];
		uint8_t eth_src[6];
		uint16_t eth_type;

		uint16_t arp_htype;
		uint16_t arp_ptype;
		uint8_t arp_hlen;
		uint8_t arp_plen;
		uint16_t arp_oper;
		uint8_t arp_smac[6];
		uint8_t arp_sip[4];
		uint8_t arp_tmac[6];
		uint8_t arp_tip[4];
	};
#pragma pack(pop)
}

void network_interface_implementation::fix(const address_v4 &me, const address_v4 &him, const logger &log)
{
	arp_packet pkt;
	pkt.eth_type = ethertype_arp;
	pkt.arp_htype = htype_ethernet;
	pkt.arp_ptype = ptype_ipv4;
	pkt.arp_hlen = hlen_ethernet;
	pkt.arp_plen = plen_ipv4;
	pkt.arp_oper = operation_reply;
	memset(pkt.eth_dst, 255, 6);
	memset(pkt.arp_tmac, 255, 6);
	memcpy(pkt.eth_src, mac, 6);
	memcpy(pkt.arp_smac, mac, 6);
	memcpy(pkt.arp_sip, me.to_bytes().data(), 4);
	memcpy(pkt.arp_tip, him.to_bytes().data(), 4);

	if(pcap_sendpacket(pcap, pkt.eth_dst, sizeof(pkt))) {
		throw pcap_error(pcap_geterr(pcap));
	}
}
