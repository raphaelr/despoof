#include <iostream>
#include <boost/format.hpp>
#include <despoof/import/log.h>
#include <despoof/common-log/logger-util.h>

using namespace std;
using namespace boost;
using namespace despoof;

static void xlog(int severity, const string &text)
{
	despoof::log(cout, severity, text);
}

extern "C" log_function __declspec(dllexport) getlog()
{
	return xlog;
}
