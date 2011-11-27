#pragma once

#include "targetwindows.h"
#include <stdexcept>

struct windows_error : public std::runtime_error {
	explicit windows_error(const std::string &text)
		: runtime_error(text)
	{
	}
};

void _throw_windows_error(const char *func, const char *file, unsigned line, DWORD error);
#define throw_windows_error2(func, error) _throw_windows_error(func, __FILE__, __LINE__, error);
#define throw_windows_error(func) _throw_windows_error(func, __FILE__, __LINE__, GetLastError());
