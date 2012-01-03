#pragma once

#include <despoof/win32/targetwindows.h>
#include <despoof/win32/error.h>
#include <string>
#include <boost/format.hpp>
#include "operations.h"

using boost::format;
using namespace std;

static string svcpath();

void despoof::install(const configuration &config)
{
	auto path = (format("\"%1%\" %2%") % svcpath() % config.args).str();
	if(!config.debugger.empty()) {
		path = (format("%1% %2%") % config.debugger % path).str();
	}

	auto sc = sc_manager(SC_MANAGER_CREATE_SERVICE);
	auto svc = CreateService(sc, "Despoof", NULL,
		SERVICE_CHANGE_CONFIG | DELETE, SERVICE_WIN32_OWN_PROCESS, config.start_type, SERVICE_ERROR_NORMAL, path.c_str(), NULL,
		NULL, NULL, "NT AUTHORITY\\LocalService", NULL);
	if(!svc) {
		auto error = GetLastError();
		if(error == ERROR_DUPLICATE_SERVICE_NAME || error == ERROR_SERVICE_EXISTS) {
			printf("The despoof service is already installed.");
			return;
		} else {
			throw_windows_error2("CreateService", error);
		}
	}

	SERVICE_DESCRIPTION sd = { "Defense against ARP spoofing - Regularly updates the ARP caches of the configured gateways with the local MAC address" };
	if(ChangeServiceConfig2(svc, SERVICE_CONFIG_DESCRIPTION, &sd)) {
		printf("Service successfully installed.");
	} else {
		DeleteService(svc);
		throw_windows_error("ChangeServiceConfig2");
	}

	CloseServiceHandle(sc);
	CloseServiceHandle(svc);
}

static string svcpath()
{
	string filename;
	filename.resize(MAX_PATH);
	if(!GetModuleFileName(NULL, &filename[0], filename.size())) {
		throw_windows_error("GetModuleFileName");
	}

	filename.resize(filename.rfind('\\')+1);
	return filename + "despoof-svc.exe";
}
