#pragma once

#include <despoof/win32/abortable.h>
#include <despoof/network_interface.h>
#include <despoof/logger.h>
#include <list>
#include <memory>

namespace despoof {
	struct network_api {
		typedef std::list<std::shared_ptr<network_interface>> interface_container;

		virtual interface_container collect_interfaces(logger &log) = 0;
		virtual bool invalid() = 0;
		virtual void wait_until_invalid(win32::abortable &ab) = 0;

		virtual ~network_api() { }
	};
}
