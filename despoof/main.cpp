#include <despoof/win32/targetwindows.h>
#include <algorithm>
#include <despoof/network_interface.h>
#include <despoof/import.h>
#include <despoof/win32/error.h>

using namespace std;
using namespace despoof;

int wmain()
{
	auto module = LoadLibrary(L"nw-sendarp.dll");
	if(!module) {
		throw_windows_error(L"LoadLibrary");
	}
	auto raw_getcollect = GetProcAddress(module, "getcollect");
	if(!raw_getcollect) {
		throw_windows_error(L"GetProcAddress");
	}
	auto getcollect = static_cast<getcollect_function>(static_cast<void*>(raw_getcollect));

	auto interfaces = getcollect()();
	for_each(interfaces.begin(), interfaces.end(), [](shared_ptr<network_interface> &iface) {
		wprintf(L" - %ls\n", iface->name().c_str());
		for_each(iface->addresses().begin(), iface->addresses().end(), [](const boost::asio::ip::address_v4 &addr) {
			wprintf(L"     Address: %hs\n", addr.to_string().c_str());
		});
		for_each(iface->gateways().begin(), iface->gateways().end(), [](const boost::asio::ip::address_v4 &addr) {
			wprintf(L"     Gateway: %hs\n", addr.to_string().c_str());
		});
	});
}
