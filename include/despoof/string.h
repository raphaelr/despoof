#pragma once

#include <string>

namespace despoof {
	std::wstring widen(const std::string &str)
	{
		return std::wstring(str.begin(), str.end());
	}
}
