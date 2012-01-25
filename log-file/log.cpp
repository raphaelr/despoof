#include <despoof/win32/targetwindows.h>
#include <fstream>
#include <boost/format.hpp>
#include <boost/date_time.hpp>
#include <boost/filesystem/fstream.hpp>
#include <despoof/import/log.h>
#include <despoof/folders.h>
#include <despoof/common-log/logger-util.h>
#include <despoof/loglevels.h>

using namespace std;
using namespace boost;
using namespace boost::posix_time;
using namespace despoof;
using namespace despoof::folders;

static filesystem::ofstream target;

static void xlog(int severity, const std::string &text)
{
	despoof::log(target, severity, text);
}

extern "C" log_function __declspec(dllexport) getlog()
{
	static time_facet *tf = new time_facet("%x-%X.%f");
	static locale loc(locale("C"), tf);

	auto time = (format("%1%", loc) % microsec_clock::local_time()).str();
	string::size_type pos;
	while((pos = time.find(':')) != string::npos) {
		time[pos] = '_';
	}
	while((pos = time.find('/')) != string::npos) {
		time[pos] = '-';
	}

	target.exceptions(ios_base::failbit);
	target.open(local_appdata() / despoof_folders() / (format("%1%.log") % time).str(), ios_base::out | ios_base::trunc);
	return xlog;
}
