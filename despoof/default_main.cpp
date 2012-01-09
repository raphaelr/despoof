#ifdef BUILD_DEFAULT

#include <despoof/win32/targetwindows.h>
#include <algorithm>
#include <typeinfo>
#include <boost/locale.hpp>
#include <despoof/utf_argv.h>
#include "init.h"

using boost::format;
using namespace std;
using namespace boost::locale::conv;
using namespace despoof;

static BOOL WINAPI control_handler(DWORD type);

static unique_ptr<context> ctx;
static bool keep_running = true;

static void run()
{
	SetConsoleCtrlHandler(control_handler, true);
	list<adapter_address> addresses = ctx->reload();
	while(keep_running) {
		ctx->iterate(addresses);
	}
}

int wmain(int argc, wchar_t **wargv)
{
	bool success;
	try {
		utf_argv uargv(argc, wargv);
		if(!despoof::init(argc, uargv.argv(), ctx)) {
			return 0;
		}
	} catch(exception &e) {
		fprintf(stderr, "Error (%s): %s\n", typeid(e).name(), e.what());
		throw;
	}
	
	try {
		run();
		return 0;
	} catch(exception &e) {
		ctx->log().fail(format("%1%: %2%") % typeid(e).name() % e.what());
		throw;
	}
}

static BOOL WINAPI control_handler(DWORD type)
{
	ctx->abort();
	keep_running = false;
	return true;
}

#endif
