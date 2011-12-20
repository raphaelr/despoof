#pragma once

#include <despoof/win32/targetwindows.h>
#include <despoof/win32/error.h>
#include "operations.h"

using namespace std;

void despoof::uninstall()
{
	auto sc = sc_manager(SC_MANAGER_CREATE_SERVICE);
	auto svc = OpenService(sc, "despoof", DELETE);
	if(!svc) {
		throw_windows_error("OpenService");
	}

	if(DeleteService(svc)) {
		printf("Service successfully removed.\n");
	} else {
		throw_windows_error("DeleteService");
	}

	CloseServiceHandle(sc);
	CloseServiceHandle(svc);
}
