#include <despoof/win32/targetwindows.h>
#include <algorithm>
#include <despoof/import.h>
#include "reload.h"
#include "log.h"
#include <despoof/win32/error.h>

using namespace std;
using namespace despoof;

template<typename GetFunction>
static decltype(GetFunction()()) loadsym(const wchar_t *file, const char *symbol)
{
	auto module = LoadLibrary(file);
	if(!module) {
		throw_windows_error(L"LoadLibrary");
	}
	auto raw_get = GetProcAddress(module, symbol);
	if(!raw_get) {
		throw_windows_error(L"GetProcAddress");
	}
	return static_cast<GetFunction>(static_cast<void*>(raw_get))();
}

int wmain()
{
	despoof::collect = loadsym<getcollect_function>(L"nw-sendarp.dll", "getcollect");
	despoof::log::logger = loadsym<getlog_function>(L"log-console.dll", "getlog");

	auto pairs = reload();
	for_each(pairs.begin(), pairs.end(), [](const adapter_address &address) {
		wprintf(L"%ls: %hs -> %hs\n", address.interface->name().c_str(), address.address.to_string().c_str(), address.gateway.to_string().c_str());
	});
}
