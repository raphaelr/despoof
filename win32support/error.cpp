#include <boost/format.hpp>
#include <boost/locale.hpp>
#include <despoof/win32/targetwindows.h>
#include <despoof/win32/error.h>

using namespace boost;
using namespace boost::locale::conv;

void throw_windows_error(const char *func, DWORD error)
{
	wchar_t *message;

	if(!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR) &message, 0, nullptr)) {
			throw windows_error("Fatal: FormatMessage failed");
	}
	
	throw windows_error((format("%1% failed: %2% (Error code %3%)") % func % utf_to_utf<char>(message) % error).str());
}

void throw_windows_error(const char *func)
{
	throw_windows_error(func, GetLastError());
}
