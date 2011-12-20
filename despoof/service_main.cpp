#ifdef BUILD_SERVICE

#include <stdexcept>
#include <despoof/win32/targetwindows.h>
#include <despoof/win32/error.h>
#include "init.h"

using namespace std;
using namespace despoof;

static void WINAPI service_main(DWORD argc, LPSTR *argv);

int main(int argc, char **argv)
{
	SERVICE_TABLE_ENTRY svtable[2];
	memset(svtable, 0, sizeof(svtable));
	svtable->lpServiceName = "despoof";
	svtable->lpServiceProc = service_main;

	if(!StartServiceCtrlDispatcher(svtable)) {
		auto error = GetLastError();
		assert(error != ERROR_INVALID_DATA && error != ERROR_SERVICE_ALREADY_RUNNING);
		if(error == ERROR_FAILED_SERVICE_CONTROLLER_CONNECT) {
			fprintf(stderr, "%s\n", "This program must be run as a service. The non-service version of despoof is called \"despoof.exe\".");
			return 1;
		} else {
			throw_windows_error2("StartServiceCtrlDispatcher", error);
		}
	}
}

static unique_ptr<context> ctx;
static bool keep_running = true;

static DWORD WINAPI control_handler(DWORD control, DWORD event_type, void *event_data, void *context);
const DWORD accepted_controls = SERVICE_ACCEPT_STOP;

static void WINAPI service_main(DWORD argc, LPSTR *argv)
{
	auto status_handle = RegisterServiceCtrlHandlerEx("despoof", control_handler, NULL);
	if(!status_handle) {
		throw_windows_error("RegisterServiceCtrlHandlerEx");
	}

	SERVICE_STATUS status = {0};
	status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	status.dwCurrentState = SERVICE_RUNNING;
	status.dwControlsAccepted = 0;
	
	SetServiceStatus(status_handle, &status);

	try {
		if(despoof_init(argc, argv, ctx)) {
			status.dwControlsAccepted = accepted_controls;
			SetServiceStatus(status_handle, &status);
			
			list<adapter_address> addresses = ctx->reload();
			while(keep_running) {
				ctx->iterate(addresses);
			}
		} else {
			status.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
			status.dwServiceSpecificExitCode = 1;
		}
	} catch(exception&) {
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
