#include <despoof/win32/targetwindows.h>
#include <algorithm>
#include <despoof/import.h>
#include "reload.h"
#include "log.h"
#include "configuration.h"
#include <despoof/win32/error.h>

using namespace std;
using namespace despoof;
using boost::format;

template<typename GetFunction>
static decltype(GetFunction()()) loadsym(const char *file, const char *symbol)
{
	auto module = LoadLibrary(file);
	if(!module) {
		throw_windows_error("LoadLibrary");
	}
	auto raw_get = GetProcAddress(module, symbol);
	if(!raw_get) {
		throw_windows_error("GetProcAddress");
	}
	return static_cast<GetFunction>(static_cast<void*>(raw_get))();
}

int main(int argc, char **argv)
{
	configuration config;
	try {
		config = configuration::load(argc, argv);
	} catch(const configuration_error &e) {
		e.print_errors();
		return 1;
	}

	printf("Interval: %i\n", config.interval);

	despoof::collect = loadsym<getcollect_function>("nw-sendarp.dll", "getcollect");
	despoof::log::logger = loadsym<getlog_function>("log-console.dll", "getlog");

	auto pairs = reload();
	for_each(pairs.begin(), pairs.end(), [](const adapter_address &address) {
		log::info(format("%1%: %2% -> %3%\n") % address.interface->name() % address.address.to_string() % address.gateway.to_string());
	});
}
