#include <iostream>
#include <boost/format.hpp>
#include <despoof/import.h>
#include <despoof/loglevels.h>

using namespace std;
using namespace boost;
using namespace despoof;

static wchar_t* severitytext(int severity)
{
	switch(severity) {
	case log_info:
		return L"INFO";
	default:
		return L"????";
	}
}

static void log(int severity, const wstring &text)
{
	wcout << wformat(L"[%1%] %2%") % severitytext(severity) % text << endl;
}

extern "C" log_function __declspec(dllexport) getlog()
{
	return log;
}
