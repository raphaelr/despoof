#pragma once

namespace despoof {
	struct configuration {
		static const int auto_start = 2;
		static const int demand_start = 3;
		static const int disabled = 4;

		configuration();

		int start_type;

		bool install;
		bool uninstall;

		bool start;
		bool stop;

		bool _nostart;
	};
}
