#pragma once

#include "targetwindows.h"
#include <string>

class windows_error {
	std::wstring what_;
public:
	windows_error(const std::wstring &what) : what_(what) { }

	const std::wstring& what() const { return what_; };
};

#define WIN32SUPPORT_WIDEN2(x) L##x
#define WIN32SUPPORT_WIDEN(x) WIN32SUPPORT_WIDEN2(x)
#define WIN32SUPPORT_WFILE WIN32SUPPORT_WIDEN(__FILE__)

void _throw_windows_error(const wchar_t *func, const wchar_t *file, unsigned line, DWORD error);
#define throw_windows_error2(func, error) _throw_windows_error(func, WIN32SUPPORT_WFILE, __LINE__, error);
#define throw_windows_error(func) _throw_windows_error(func, WIN32SUPPORT_WFILE, __LINE__, GetLastError());
