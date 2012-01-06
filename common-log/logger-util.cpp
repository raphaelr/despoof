#include <boost/locale.hpp>
#include <despoof/loglevels.h>
#include <despoof/common-log/logger-util.h>

using namespace boost::locale;
using namespace std;
using namespace despoof;

static char* severitytext(int severity)
{
	switch(severity) {
	case log_info:
		return "INFO";
	case log_warn:
		return "WARN";
	case log_fail:
		return "FAIL";
	default:
		return "????";
	}
}

static locale& loglocale()
{
	static locale loc(generator().generate(""));
	return loc;
}

void despoof::log(ostream &target, int severity, const string &text)
{
	auto prev = target.imbue(loglocale());
	target << "[" << severitytext(severity) << " " << as::datetime << time(0) << "] " << text << endl;
	target.flush();
	target.imbue(prev);
}
