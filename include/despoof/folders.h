#pragma once

#include <string>
#include <vector>
#include <stdexcept>

namespace despoof { namespace folders {
	std::string local_appdata();
	std::string join_folders(const std::vector<std::string> &folders);
	
	const std::vector<std::string>& despoof_folders();
	const std::string& despoof_local_appdata();

	struct folder_not_found : public std::runtime_error {
		folder_not_found(const std::string &foldername);
	};
}}
