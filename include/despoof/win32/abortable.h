#pragma once

namespace despoof { namespace win32 {
	class abortable {
		void *event_;
		bool aborting_;
	public:
		abortable();

		void abort();
		void* wait_event();
		bool aborting();
	};
}}
