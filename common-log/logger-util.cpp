#include <boost/format.hpp>
#include <despoof/logger-util.h>
#include <despoof/loglevels.h>

using boost::format;
using namespace std;
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

void despoof::log(ostream &target, int severity, const string &text)
{
	target << format("[%1%] %2%") % severitytext(severity) % text << endl;
	target.flush();
}
