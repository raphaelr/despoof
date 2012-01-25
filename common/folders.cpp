#include <despoof/win32/targetwindows.h>
#include <despoof/win32/error.h>
#include <ShlObj.h>
#include <algorithm>
#include <assert.h>
#include <boost/locale.hpp>
#include <despoof/folders.h>

using namespace std;
using namespace boost::locale::conv;
using namespace despoof::folders;

string despoof::folders::local_appdata()
{
	wstring buffer;
	buffer.resize(MAX_PATH);
	auto result = SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, &buffer[0]);
	assert(result != E_INVALIDARG);
	if(result == S_FALSE) {
		throw folder_not_found("local application data");
	}
	buffer.resize(buffer.find_first_of((wchar_t) 0));
	return utf_to_utf<char>(buffer);
}

string despoof::folders::join_folders(const std::vector<std::string> &folders)
{
	string path;
	for_each(folders.begin(), folders.end(), [&](const std::string &str) {
		if(!path.empty()) { path += '/'; }
		path += str;
		if(!CreateDirectory(utf_to_utf<wchar_t>(path).c_str(), NULL)) {
			auto error = GetLastError();
			if(error != ERROR_ALREADY_EXISTS) {
				throw_windows_error("CreateDirectory", error);
			}
		}
	});
	return path;
}

string despoof::folders::join_folders(const std::string &base, const std::vector<std::string> &folders)
{
	vector<string> result;
	result.push_back(local_appdata());
	result.insert(folders.end(), folders.begin(), folders.end());
	return join_folders(result);
}

const vector<string>& despoof::folders::despoof_folders()
{
	static vector<string> folders;
	static int init = [&]() -> int {
		folders.push_back("tape software");
		folders.push_back("despoof");
		return 0;
	}();

	return folders;
}

folder_not_found::folder_not_found(const string &foldername)
	: runtime_error("The " + foldername + " folder does not exist")
{
}
