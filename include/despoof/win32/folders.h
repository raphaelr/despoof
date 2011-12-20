#pragma once

#include <string>
#include <vector>
#include <stdexcept>

namespace despoof { namespace win32 {
	std::string appdata();
	std::string appdata(const std::vector<std::string> &folders);
	std::string despoof_appdata();

	struct folder_not_found : public std::runtime_error {
		folder_not_found(const std::string &foldername);
	};
}}
