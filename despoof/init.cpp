#include <despoof/win32/targetwindows.h>
#include <algorithm>
#include <boost/locale.hpp>
#include "context.h"
#include "command_line.h"
#include "init.h"
#include <despoof/import/log.h>
#include <despoof/import/collect.h>
#include <despoof/win32/error.h>

using boost::format;
using boost::locale::generator;
using namespace std;
using namespace boost::locale::conv;
using namespace despoof;

template<typename GetFunction>
static GetFunction loadsym(const string &file, const char *symbol)
{
	auto module = LoadLibrary(utf_to_utf<wchar_t>(file).c_str());
	if(!module) {
		throw_windows_error("LoadLibrary");
	}
	auto raw_get = GetProcAddress(module, symbol);
	if(!raw_get) {
		throw_windows_error("GetProcAddress");
	}
	return static_cast<GetFunction>(static_cast<void*>(raw_get));
}

static string modfile(const char *prefix, const string &name)
{
	return (format("%1%-%2%.dll") % prefix % name).str();
}

bool despoof::init(int argc, char **argv, unique_ptr<context> &ctx)
{
	locale::global(generator().generate(""));

	configuration config;
	try {
		command_line_to_configuration(config, argc, argv);
	} catch(const command_line_error &e) {
		e.print_errors();
		return false;
	}
	
	if(config._nostart) { return false; }

	ctx.reset(new context(config, unique_ptr<network_api>(loadsym<getapi_function>(modfile("nw", config.nw_module), "getapi")()), loadsym<getlog_function>(modfile("log", config.log_module), "getlog")()));
	return true;
}
