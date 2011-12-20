#include <despoof/win32/targetwindows.h>
#include <despoof/win32/error.h>
#include <ShlObj.h>
#include <algorithm>
#include <assert.h>
#include <despoof/win32/folders.h>

using namespace std;
using namespace despoof::win32;

string despoof::win32::appdata()
{
	string buffer;
	buffer.resize(MAX_PATH);
	auto result = SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, &buffer[0]);
	assert(result != E_INVALIDARG);
	if(result == S_FALSE) {
		throw folder_not_found("local application data");
	}
	buffer.resize(buffer.find_first_of((char) 0));
	return buffer;
}

string despoof::win32::appdata(const std::vector<std::string> &folders)
{
	string path = appdata();
	for_each(folders.begin(), folders.end(), [&](const std::string &str) {
		path += '/' + str;
		if(!CreateDirectory(path.c_str(), NULL)) {
			auto error = GetLastError();
			if(error != ERROR_ALREADY_EXISTS) {
				throw_windows_error2("CreateDirectory", error);
			}
		}
	});
	return path;
}

static vector<string> get_despoof_folders()
{
	vector<string> folders;
	folders.push_back("tape software");
	folders.push_back("despoof");
	return folders;
}
string despoof::win32::despoof_appdata()
{
	static vector<string> folders = get_despoof_folders();
	return appdata(folders);
}

folder_not_found::folder_not_found(const string &foldername)
	: runtime_error("The " + foldername + " folder does not exist")
{
}
