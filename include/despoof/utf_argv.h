#include <string>
#include <vector>

namespace despoof {
	class utf_argv {
		std::vector<std::string> xargv;
		std::vector<char*> vargv;
	public:
		utf_argv(int argc, const wchar_t * const *wargv);

		char** argv();
	};
}
