#include <despoof/common-nw/common_network_interface.h>

using namespace boost::asio::ip;
using namespace despoof::win32;

template<class Container> static void address_list_into_container(Container &dst, const IP_ADDR_STRING &list);

common_network_interface::common_network_interface(const IP_ADAPTER_INFO *info)
	: name_(info->Description, info->Description + strlen(info->Description))
{
	address_list_into_container(addresses_, info->IpAddressList);
	address_list_into_container(gateways_, info->GatewayList);
}

template<class Container>
static void address_list_into_container<Container>(Container &dst, const IP_ADDR_STRING &list)
{
	for(auto address = &list; address; address = address->Next) {
		if(!strcmp("", address->IpAddress.String)) { continue; }
		auto addr = address_v4::from_string(address->IpAddress.String);
		if(addr != address_v4::any()) {
			dst.push_back(addr);
		}
	}
}
