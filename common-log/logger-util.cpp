#include <boost/format.hpp>
#include <boost/date_time.hpp>
#include <despoof/logger-util.h>
#include <despoof/loglevels.h>

using boost::format;
using namespace boost::date_time;
using namespace boost::local_time;
using namespace std;
using namespace despoof;

static local_time_facet ltf("%x %X");

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
	auto now = boost::posix_time::second_clock::local_time();

	target.imbue(locale(target.getloc(), &ltf));
	target << format("[%1% %2%] %3%") % severitytext(severity) % now % text << endl;
	target.flush();
}
