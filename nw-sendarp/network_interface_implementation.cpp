#include "network_interface_implementation.h"

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

template<class Container>
static void address_list_into_container<Container>(Container &dst, const IP_ADDR_STRING &list)
{
	for(auto address = &list; address; address = address->Next) {
		dst.push_back(address_v4::from_string(address->IpAddress.String));
	}
}
