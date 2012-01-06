#pragma once

#include <string>
#include <vector>
#include <stdexcept>

namespace despoof { namespace win32 {
	std::wstring appdata();
	std::wstring appdata(const std::vector<std::wstring> &folders);
	std::wstring despoof_appdata();

	struct folder_not_found : public std::runtime_error {
		folder_not_found(const std::string &foldername);
	};
}}
