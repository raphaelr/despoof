#include "network_interface_implementation.h"
#include "pcap_exception.h"
#include <vector>
#include <stdint.h>
#include <WinSock2.h>
#include <despoof/win32/error.h>

using namespace std;
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
	copy(info->Address, info->Address + 6, interface_mac.begin());
	reload_arp_table();
}

network_interface_implementation::~network_interface_implementation()
{
	if(pcap) {
		pcap_close(pcap);
	}
}

void network_interface_implementation::reload_arp_table()
{
	vector<uint8_t> buffer;
	ULONG size = buffer.size();
	DWORD error;
	do {
		error = GetIpNetTable(reinterpret_cast<MIB_IPNETTABLE*>(buffer.data()), &size, false);
		switch(error) {
		case NO_ERROR:
		case ERROR_NO_DATA:
			break;
		case ERROR_INSUFFICIENT_BUFFER:
			buffer.resize(size);
			break;
		case ERROR_INVALID_PARAMETER:
			assert(!"GetIpNetTable returned ERROR_INVALID_PARAMETER");
		default:
			throw_windows_error2("GetIpNetTable", error);
		}
	} while(error != NO_ERROR && error != ERROR_NO_DATA);

	auto table = reinterpret_cast<MIB_IPNETTABLE*>(buffer.data());
	arp_table.clear();
	for(int i=0; i < table->dwNumEntries; i++) {
		auto &row = table->table[i];
		if(row.dwType != MIB_IPNET_TYPE_DYNAMIC && row.dwType != MIB_IPNET_TYPE_STATIC) { continue; }

		mac_address mac;
		copy(row.bPhysAddr, row.bPhysAddr + 6, mac.begin());
		arp_table[address_v4(ntohl(row.dwAddr))] = mac;
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
	mac_address him_mac;
	if(!mac_for(him_mac, me, him, log)) {
		return;
	}
	
	arp_packet pkt;
	pkt.eth_type = ethertype_arp;
	pkt.arp_htype = htype_ethernet;
	pkt.arp_ptype = ptype_ipv4;
	pkt.arp_hlen = hlen_ethernet;
	pkt.arp_plen = plen_ipv4;
	pkt.arp_oper = operation_reply;
	memcpy(pkt.eth_src, interface_mac.data(), 6);
	memcpy(pkt.arp_smac, interface_mac.data(), 6);
	memcpy(pkt.eth_dst, him_mac.data(), 6);
	memcpy(pkt.arp_tmac, him_mac.data(), 6);;
	memcpy(pkt.arp_sip, me.to_bytes().data(), 4);
	memcpy(pkt.arp_tip, him.to_bytes().data(), 4);

	if(pcap_sendpacket(pcap, pkt.eth_dst, sizeof(pkt))) {
		throw pcap_error(pcap_geterr(pcap));
	}
}

bool network_interface_implementation::mac_for(mac_address &output, const address_v4 &me, const address_v4 &him, const logger &log)
{
	auto iter = arp_table.find(him);
	if(iter != arp_table.end()) {
		output = iter->second;
		return true;
	}

	log.info(format("MAC address for %1% not found; reloading ARP table") % him.to_string());
	reload_arp_table();
	iter = arp_table.find(him);
	if(iter != arp_table.end()) {
		output = iter->second;
		return true;
	}

	log.info(format("MAC address for %1% not found; Sending ARP request") % him.to_string());
	ULONG size = output.size();
	auto error = SendARP(ntohl(him.to_ulong()), ntohl(me.to_ulong()), reinterpret_cast<ULONG*>(output.data()), &size);
	switch(error) {
	case NO_ERROR:
		return true;
	case ERROR_BAD_NET_NAME:
	case ERROR_GEN_FAILURE:
		log.warn(format("No reply received - skipping %1%") % him.to_string());
		break;
	case ERROR_BUFFER_OVERFLOW:
	case ERROR_INVALID_PARAMETER:
	case ERROR_INVALID_USER_BUFFER:
		assert(!"SendARP returned ERROR_BUFFER_OVERFLOW/INVALID_PARAMETER/INVALID_USER_BUFFER");
	default:
		throw_windows_error2("SendARP", error);
	}
	return false;
}
