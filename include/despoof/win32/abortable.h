#pragma once

namespace despoof { namespace win32 {
	class abortable {
		bool abort_pending_;
		bool abortable_;
		void *thread_;

		static void __stdcall apcproc(__w64 unsigned long self);

		void abort_apc();
	public:
		abortable();

		void abort();
		bool abort_pending();
		void recognize_abort(bool state);
	};
}}
