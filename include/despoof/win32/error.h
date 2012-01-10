#pragma once

#include "targetwindows.h"
#include <stdexcept>

struct windows_error : public std::runtime_error {
	explicit windows_error(const std::string &text)
		: runtime_error(text)
	{
	}
};

void throw_windows_error(const char *func, DWORD error);
void throw_windows_error(const char *func);
