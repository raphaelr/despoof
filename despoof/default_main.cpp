#ifdef BUILD_DEFAULT

#include <despoof/win32/targetwindows.h>
#include "init.h"

using namespace std;
using namespace despoof;

static BOOL WINAPI control_handler(DWORD type);

static unique_ptr<context> ctx;
static bool keep_running = true;

int main(int argc, char **argv)
{
	SetConsoleCtrlHandler(control_handler, true);

	if(despoof_init(argc, argv, ctx)) {
		list<adapter_address> addresses = ctx->reload();
		while(keep_running) {
			ctx->iterate(addresses);
		}
		return 0;
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
