#include <boost/format.hpp>
#include <despoof/win32/targetwindows.h>
#include <despoof/win32/error.h>

using namespace boost;

void _throw_windows_error(const wchar_t *func, const wchar_t *file, unsigned line, DWORD error)
{
	wchar_t *message;

	if(!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR) &message, 0, nullptr)) {
			throw windows_error(L"Fatal: FormatMessage failed");
	}
	
	throw windows_error((wformat(L"%1% failed: %2% (From %3%#%4%) (Error code %5%)") % func % message % file % line % error).str());
}
