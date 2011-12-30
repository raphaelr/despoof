#ifdef BUILD_DEFAULT

#include <despoof/win32/targetwindows.h>
#include <typeinfo>
#include "init.h"

using boost::format;
using namespace std;
using namespace despoof;

static BOOL WINAPI control_handler(DWORD type);

static unique_ptr<context> ctx;
static bool keep_running = true;

static void run()
{
	list<adapter_address> addresses = ctx->reload();
	while(keep_running) {
		ctx->iterate(addresses);
	}
}

int main(int argc, char **argv)
{
	SetConsoleCtrlHandler(control_handler, true);

	bool success;
	try {
		success = despoof_init(argc, argv, ctx);
	} catch(exception &e) {
		fprintf(stderr, "Error (%s): %s\n", typeid(e).name(), e.what());
		throw;
	}

	if(success) {
		try {
			run();
			return 0;
		} catch(exception &e) {
			ctx->log().fail(format("%1%: %2%") % typeid(e).name() % e.what());
			throw;
		}
	} else {
		return 1;
	}
}

static BOOL WINAPI control_handler(DWORD type)
{
	ctx->abort();
	keep_running = false;
	return true;
}

#endif
