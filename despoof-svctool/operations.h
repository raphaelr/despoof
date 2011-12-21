#pragma once

#include <despoof/win32/targetwindows.h>
#include "configuration.h"

namespace despoof {
	SC_HANDLE sc_manager(DWORD access);

	void install(const configuration &config);
	void uninstall(const configuration &config);
}
