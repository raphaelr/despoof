#include "network_interface_implementation.h"
#include <WinSock2.h>
#include <despoof/win32/error.h>

using namespace std;
using namespace boost::asio::ip;
using namespace despoof;
using namespace despoof::win32;

template<class Container> static void address_list_into_container(Container &dst, const IP_ADDR_STRING &list);

network_interface_implementation::network_interface_implementation(const IP_ADAPTER_INFO *info)
	: name_(info->Description, info->Description + strlen(info->Description))
{
	address_list_into_container(addresses_, info->IpAddressList);
	address_list_into_container(gateways_, info->GatewayList);
}

void network_interface_implementation::fix(const boost::asio::ip::address_v4 &me, const boost::asio::ip::address_v4 &him)
{
	ULONG mac[2];
	ULONG size = sizeof(mac);

	auto result = SendARP(ntohl(him.to_ulong()), ntohl(me.to_ulong()), mac, &size);
	switch(result) {
	case ERROR_GEN_FAILURE:
	case ERROR_BAD_NET_NAME:
		// No ARP reply
	case ERROR_NOT_FOUND:
		// Source IP (me) does not exist
		break;
	default:
		throw_windows_error2("network_interface_implementation::fix [nw-sendarp.dll]", result);
	}
}

template<class Container>
static void address_list_into_container<Container>(Container &dst, const IP_ADDR_STRING &list)
{
	for(auto address = &list; address; address = address->Next) {
		auto addr = address_v4::from_string(address->IpAddress.String);
		if(addr != address_v4::any()) {
			dst.push_back(addr);
		}
	}
}
