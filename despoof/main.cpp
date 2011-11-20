#include <algorithm>
#include <despoof/network_interface.h>

using namespace std;
using namespace despoof;

int wmain()
{
	auto interfaces = network_interface::collect();
	for_each(interfaces.begin(), interfaces.end(), [](unique_ptr<network_interface> &iface) {
		wprintf(L" - %ls\n", iface->name().c_str());
		for_each(iface->addresses().begin(), iface->addresses().end(), [](const boost::asio::ip::address_v4 &addr) {
			wprintf(L"     Address: %hs\n", addr.to_string().c_str());
		});
		for_each(iface->gateways().begin(), iface->gateways().end(), [](const boost::asio::ip::address_v4 &addr) {
			wprintf(L"     Gateway: %hs\n", addr.to_string().c_str());
		});
	});
}
