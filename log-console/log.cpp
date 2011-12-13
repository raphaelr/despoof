#include <iostream>
#include <boost/format.hpp>
#include <despoof/import/log.h>
#include <despoof/loglevels.h>

using namespace std;
using namespace boost;
using namespace despoof;

static char* severitytext(int severity)
{
	switch(severity) {
	case log_info:
		return "INFO";
	case log_warn:
		return "WARN";
	default:
		return "????";
	}
}

static void log(int severity, const string &text)
{
	cout << format("[%1%] %2%") % severitytext(severity) % text << endl;
}

extern "C" log_function __declspec(dllexport) getlog()
{
	return log;
}
