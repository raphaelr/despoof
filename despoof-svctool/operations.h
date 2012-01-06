#pragma once

#include <despoof/win32/targetwindows.h>
#include <despoof/config.h>
#include "configuration.h"

namespace despoof {
	struct silent_exit { };

	SC_HANDLE sc_manager(DWORD access = 0);
	SC_HANDLE open_despoof_service(SC_HANDLE sc, DWORD access);

	void install(const configuration &config);
	void uninstall(const configuration &config);
	void start(const configuration &config);
	void stop(const configuration &config);
}
