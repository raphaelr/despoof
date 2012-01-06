#include <despoof/win32/error.h>
#include "operations.h"

using namespace despoof;

SC_HANDLE despoof::sc_manager(DWORD access)
{
	auto result = OpenSCManager(NULL, NULL, access);
	if(!result) {
		throw_windows_error("OpenSCManager");
	}
	return result;
}

SC_HANDLE despoof::open_despoof_service(SC_HANDLE sc, DWORD access)
{
	auto result = OpenService(sc, DESPOOF_WIDE_SERVICE_NAME, access);
	if(!result) {
		auto error = GetLastError();
		if(error == ERROR_SERVICE_DOES_NOT_EXIST) {
			printf("The service is not installed.");
			throw silent_exit();
		} else {
			throw_windows_error2("OpenService", error);
		}
	}
	return result;
}
