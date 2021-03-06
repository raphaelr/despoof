#pragma once

#include <despoof/win32/targetwindows.h>
#include <despoof/win32/error.h>
#include "operations.h"

using namespace std;

void despoof::uninstall(const configuration &config)
{
	auto sc = sc_manager();
	auto svc = open_despoof_service(sc, DELETE);

	if(DeleteService(svc)) {
		printf("Service successfully removed.");
	} else {
		throw_windows_error("DeleteService");
	}

	CloseServiceHandle(sc);
	CloseServiceHandle(svc);
}
