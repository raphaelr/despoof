#include <boost/locale.hpp>
#include <despoof/utf_argv.h>

using namespace std;
using namespace boost::locale::conv;
using namespace despoof;

utf_argv::utf_argv(int argc, const wchar_t * const *wargv)
	: xargv(argc), vargv(argc)
{
	transform(wargv, wargv + argc, xargv.begin(), [](const wchar_t *ws) { return utf_to_utf<char>(ws); });
	transform(xargv.begin(), xargv.end(), vargv.begin(), [](string &str) { return &str[0]; });
}

char** utf_argv::argv()
{
	return vargv.data();
}
