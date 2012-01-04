#include <despoof/win32/error.h>
#include <ShellAPI.h>
#include "operations.h"

using namespace std;;
using namespace despoof;

void despoof::start(const configuration &config)
{
	int argc;
	auto argv = CommandLineToArgvW((L"despoof-svc " + wstring(config.args.begin(), config.args.end())).c_str(), &argc);
	if(!argv) {
		throw_windows_error("CommandLineToArgvW");
	}

	auto sc = sc_manager();
	auto svc = open_despoof_service(sc, SERVICE_START);

	printf("Starting service...\n");
	if(StartServiceW(svc, argc, const_cast<LPCWSTR*>(argv))) {
		printf("Service successfully started.");
	} else {
		auto error = GetLastError();
		if(error == ERROR_SERVICE_ALREADY_RUNNING) {
			printf("The service is already running.");
		} else {
			throw_windows_error2("StartService", error);
		}
	}
}
