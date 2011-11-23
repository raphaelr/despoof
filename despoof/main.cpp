#include <despoof/win32/targetwindows.h>
#include <algorithm>
#include <despoof/import.h>
#include "reload.h"
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
	despoof::collect = getcollect();

	auto pairs = reload();
	for_each(pairs.begin(), pairs.end(), [](const adapter_address &address) {
		wprintf(L"%ls: %hs -> %hs\n", address.interface->name().c_str(), address.address.to_string().c_str(), address.gateway.to_string().c_str());
	});
}
