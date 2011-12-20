#include <despoof/win32/targetwindows.h>
#include <algorithm>
#include "context.h"
#include "command_line.h"
#include <despoof/import/log.h>
#include <despoof/import/collect.h>
#include <despoof/win32/error.h>

using namespace std;
using namespace despoof;
using boost::format;

template<typename GetFunction>
static GetFunction loadsym(const char *file, const char *symbol)
{
	auto module = LoadLibrary(file);
	if(!module) {
		throw_windows_error("LoadLibrary");
	}
	auto raw_get = GetProcAddress(module, symbol);
	if(!raw_get) {
		throw_windows_error("GetProcAddress");
	}
	return static_cast<GetFunction>(static_cast<void*>(raw_get));
}

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "");
	_tzset();

	configuration config;
	try {
		command_line_to_configuration(config, argc, argv);
	} catch(const command_line_error &e) {
		e.print_errors();
		return 1;
	}
	if(config._nostart) { return 0; }

	printf("Interval: %i\n", config.interval);

	context ctx(config, unique_ptr<network_api>(loadsym<getapi_function>("nw-sendarp.dll", "getapi")()), loadsym<getlog_function>("log-console.dll", "getlog")());
	
	while(true) {
		list<adapter_address> addresses = ctx.reload();
		ctx.iterate(addresses);
	}
}
