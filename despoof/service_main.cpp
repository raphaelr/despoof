#ifdef BUILD_SERVICE

#include <despoof/win32/targetwindows.h>
#include <despoof/win32/error.h>
#include <stdexcept>
#include <typeinfo>
#include <despoof/config.h>
#include <despoof/utf_argv.h>
#include "init.h"

using boost::format;
using namespace std;
using namespace despoof;

static void WINAPI service_main(DWORD argc, LPWSTR *argv);

int main(int argc, char **argv)
{
	SERVICE_TABLE_ENTRY svtable[2];
	memset(svtable, 0, sizeof(svtable));
	svtable->lpServiceName = DESPOOF_WIDE_SERVICE_NAME;
	svtable->lpServiceProc = service_main;

	if(!StartServiceCtrlDispatcher(svtable)) {
		auto error = GetLastError();
		assert(error != ERROR_INVALID_DATA && error != ERROR_SERVICE_ALREADY_RUNNING);
		if(error == ERROR_FAILED_SERVICE_CONTROLLER_CONNECT) {
			fprintf(stderr, "%s\n", "This program must be run as a service. The non-service version of despoof is called \"despoof.exe\".");
			return 1;
		} else {
			throw_windows_error("StartServiceCtrlDispatcher", error);
		}
	}
}

static unique_ptr<context> ctx;
static bool keep_running = true;

static DWORD WINAPI control_handler(DWORD control, DWORD event_type, void *event_data, void *context);
const DWORD accepted_controls = SERVICE_ACCEPT_STOP;

static void WINAPI service_main(DWORD argc, LPWSTR *wargv)
{
	auto status_handle = RegisterServiceCtrlHandlerEx(DESPOOF_WIDE_SERVICE_NAME, control_handler, NULL);
	if(!status_handle) {
		throw_windows_error("RegisterServiceCtrlHandlerEx");
	}

	SERVICE_STATUS status = {0};
	status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	status.dwCurrentState = SERVICE_RUNNING;
	status.dwControlsAccepted = 0;
	
	SetServiceStatus(status_handle, &status);

	bool start;
	try {
		utf_argv uargv(argc, wargv);
		if(!despoof::init(argc, uargv.argv(), ctx)) {
			return;
		}
	} catch(exception &ex) {
		// PANIC
		status.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
		status.dwServiceSpecificExitCode = 1;
		status.dwCurrentState = SERVICE_STOPPED;
		SetServiceStatus(status_handle, &status);
	}

	status.dwControlsAccepted = accepted_controls;
	SetServiceStatus(status_handle, &status);

	try {
		list<adapter_address> addresses = ctx->reload();
		while(keep_running) {
			ctx->iterate(addresses);
		}
	} catch(exception &ex) {
		ctx->log().fail(format("%1%: %2%") % typeid(ex).name() % ex.what());
		status.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
		status.dwServiceSpecificExitCode = 1;
	}

	status.dwCurrentState = SERVICE_STOPPED;
	SetServiceStatus(status_handle, &status);
}

static DWORD WINAPI control_handler(DWORD control, DWORD event_type, void *event_data, void *context)
{
	switch(control) {
	case SERVICE_CONTROL_STOP:
		keep_running = false;
		ctx->abort();
		return NO_ERROR;
	case SERVICE_CONTROL_INTERROGATE:
		return NO_ERROR;
	}
	return ERROR_CALL_NOT_IMPLEMENTED;
}

#endif
