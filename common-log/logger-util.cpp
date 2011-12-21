#include <boost/format.hpp>
#include <boost/date_time.hpp>
#include <despoof/logger-util.h>
#include <despoof/loglevels.h>

using boost::format;
using namespace boost::posix_time;
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

void despoof::log(ostream &target, int severity, const string &text)
{
	static time_facet *tf = new time_facet("%x %X");
	static locale loc(locale(""), tf);

	auto now = second_clock::local_time();
	target << format("[%1% %2%] %3%\n", loc) % severitytext(severity) % now % text;
	target.flush();
}
