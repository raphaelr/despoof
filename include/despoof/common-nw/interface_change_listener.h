#pragma once

#include <memory>
#include <despoof/win32/abortable.h>

namespace despoof { namespace win32 {
	struct interface_change_listener {
		static std::unique_ptr<interface_change_listener> create();

		virtual ~interface_change_listener() { }

		virtual void wait(abortable &ab) = 0;
		virtual bool changed() = 0;
	};
}}
