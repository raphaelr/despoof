#include <despoof/win32/error.h>
#include "operations.h"

using namespace despoof;

void despoof::start(const configuration &config)
{
	auto sc = sc_manager();
	auto svc = open_despoof_service(sc, SERVICE_START);

	printf("Starting service...\n");
	if(StartService(svc, 0, NULL)) {
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
