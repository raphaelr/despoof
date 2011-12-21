#include <despoof/win32/targetwindows.h>
#include <despoof/win32/folders.h>
#include <fstream>
#include <ctime>
#include <boost/format.hpp>
#include <despoof/import/log.h>
#include <despoof/loglevels.h>

using namespace std;
using namespace boost;
using namespace despoof;
using namespace despoof::win32;

static ofstream target;

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
	target << format("[%1%] %2%") % severitytext(severity) % text << endl;
	target.flush();
}

extern "C" log_function __declspec(dllexport) getlog()
{
	__time64_t now;	
	_time64(&now);
	auto lt = localtime(&now);
	char buffer[256];
	auto result = strftime(buffer, sizeof(buffer), "%c", lt);
	assert(result);

	string name(buffer);
	string::size_type loc;
	while((loc = name.find(':')) != string::npos) {
		name[loc] = '_';
	}

	target.exceptions(ios_base::failbit);
	target.open((format("%1%/log-%2%#%3%.log") % despoof_appdata() % name % now).str(), ios_base::out | ios_base::trunc);
	return log;
}
