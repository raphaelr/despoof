#pragma once

#include <despoof/win32/targetwindows.h>
#include "configuration.h"

namespace despoof {
	SC_HANDLE sc_manager(DWORD access = 0);

	void install(const configuration &config);
	void uninstall(const configuration &config);
	void start(const configuration &config);
	void stop(const configuration &config);
}
