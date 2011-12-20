#pragma once

#include <despoof/win32/targetwindows.h>

namespace despoof {
	SC_HANDLE sc_manager(DWORD access);

	void install();
	void uninstall();
}
