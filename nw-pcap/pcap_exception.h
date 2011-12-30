#pragma once

#include <stdexcept>

namespace despoof { namespace win32 {
	class pcap_error : public std::runtime_error {
	public:
		pcap_error(const char *error)
			: runtime_error(error)
		{
		}
	};
}}
