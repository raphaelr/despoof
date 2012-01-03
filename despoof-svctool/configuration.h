#pragma once

#include <string>

#define DESPOOF_DEFAULT_DEBUGGER "ntsd -server npipe:pipe=despoof_debug -noio"

namespace despoof {
	struct configuration {
		static const int auto_start = 2;
		static const int demand_start = 3;
		static const int disabled = 4;

		configuration();

		int start_type;
		std::string args;
		std::string debugger; // Empty means no debugger

		bool install;
		bool uninstall;

		bool start;
		bool stop;

		bool _nostart;
	};
}
