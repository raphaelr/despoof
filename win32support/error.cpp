#include <boost/format.hpp>
#include <despoof/win32/targetwindows.h>
#include <despoof/win32/error.h>

using namespace boost;

void _throw_windows_error(const char *func, const char *file, unsigned line, DWORD error)
{
	char *message;

	if(!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR) &message, 0, nullptr)) {
			throw windows_error("Fatal: FormatMessage failed");
	}
	
	throw windows_error((format("%1% failed: %2% (From %3%#%4%) (Error code %5%)") % func % message % file % line % error).str());
}
