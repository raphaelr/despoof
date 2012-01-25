#pragma once

#include <stdexcept>
#include <boost/filesystem/path.hpp>

namespace despoof { namespace folders {
	boost::filesystem::path local_appdata();
	boost::filesystem::path despoof_folders();

	struct folder_not_found : public std::runtime_error {
		folder_not_found(const std::string &foldername);
	};
}}
