#include <despoof/win32/targetwindows.h>
#include <ShlObj.h>
#include <assert.h>
#include <despoof/folders.h>

using namespace std;
using namespace boost::filesystem;
using namespace despoof::folders;

path despoof::folders::local_appdata()
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

path despoof::folders::despoof_folders()
{
	return path("tape software") / "despoof";
}

folder_not_found::folder_not_found(const string &foldername)
	: runtime_error("The " + foldername + " folder does not exist")
{
}
