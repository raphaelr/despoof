#include <despoof/win32/error.h>
#include "operations.h"

using namespace despoof;

void despoof::start(const configuration &config)
{
	auto sc = sc_manager();
	auto svc = OpenService(sc, "despoof", SERVICE_START);
	if(!svc) {
		throw_windows_error("OpenService");
	}

	printf("Starting service...\n");
	if(StartService(svc, 0, NULL)) {
		printf("Service successfully started.");
	} else {
		throw_windows_error("StartService");
	}
}
