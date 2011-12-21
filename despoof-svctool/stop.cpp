#include <despoof/win32/error.h>
#include "operations.h"

using namespace despoof;

void despoof::stop(const configuration &config)
{
	auto sc = sc_manager();
	auto svc = open_despoof_service(sc, SERVICE_STOP);

	SERVICE_STATUS status;
	printf("Stopping service...\n");
	if(ControlService(svc, SERVICE_CONTROL_STOP, &status)) {
		printf("Service successfully stopped.");
	} else {
		throw_windows_error("ControlService");
	}
}
