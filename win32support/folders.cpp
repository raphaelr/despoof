#include <despoof/win32/targetwindows.h>
#include <despoof/win32/error.h>
#include <ShlObj.h>
#include <algorithm>
#include <assert.h>
#include <despoof/win32/folders.h>

using namespace std;
using namespace despoof::win32;

wstring despoof::win32::appdata()
{
	wstring buffer;
	buffer.resize(MAX_PATH);
	auto result = SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, &buffer[0]);
	assert(result != E_INVALIDARG);
	if(result == S_FALSE) {
		throw folder_not_found("local application data");
	}
	buffer.resize(buffer.find_first_of((wchar_t) 0));
	return buffer;
}

wstring despoof::win32::appdata(const std::vector<std::wstring> &folders)
{
	wstring path = appdata();
	for_each(folders.begin(), folders.end(), [&](const std::wstring &str) {
		path += L'/' + str;
		if(!CreateDirectory(path.c_str(), NULL)) {
			auto error = GetLastError();
			if(error != ERROR_ALREADY_EXISTS) {
				throw_windows_error2("CreateDirectory", error);
			}
		}
	});
	return path;
}

static vector<wstring> get_despoof_folders()
{
	vector<wstring> folders;
	folders.push_back(L"tape software");
	folders.push_back(L"despoof");
	return folders;
}
wstring despoof::win32::despoof_appdata()
{
	static auto folders = get_despoof_folders();
	return appdata(folders);
}

folder_not_found::folder_not_found(const string &foldername)
	: runtime_error("The " + foldername + " folder does not exist")
{
}
