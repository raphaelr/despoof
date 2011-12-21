#pragma once

namespace despoof {
	struct configuration {
		configuration();

		bool install;
		bool uninstall;

		bool start;
		bool stop;

		bool _nostart;
	};
}
