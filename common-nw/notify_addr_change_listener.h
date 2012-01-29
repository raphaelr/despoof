#pragma once

#include <despoof/win32/targetwindows.h>
#include <despoof/win32/error.h>
#include <IPHlpApi.h>
#include <assert.h>
#include <despoof/common-nw/interface_change_listener.h>

namespace despoof { namespace win32 {
	class notify_addr_change_listener : public interface_change_listener {
		HANDLE wait_handle;
		OVERLAPPED overlapped;
	public:
		notify_addr_change_listener();
		~notify_addr_change_listener();

		void reset();
		virtual void wait(abortable &ab) override;
		virtual bool changed() override;
	};

	inline notify_addr_change_listener::notify_addr_change_listener()
	{
		overlapped.hEvent = CreateEvent(NULL, true, false, NULL);
		if(!overlapped.hEvent) {
			throw_windows_error("CreateEvent");
		}
		reset();
	}

	inline notify_addr_change_listener::~notify_addr_change_listener()
	{
		CancelIPChangeNotify(&overlapped);
	}

	inline void notify_addr_change_listener::reset()
	{
		auto error = NotifyAddrChange(&wait_handle, &overlapped);
		if(error != ERROR_IO_PENDING) {
			throw_windows_error("NotifyAddrChange", error);
		}
	}

	inline void notify_addr_change_listener::wait(abortable &ab)
	{
		HANDLE objects[] = { wait_handle, ab.wait_event() };
		auto result = WaitForMultipleObjects(sizeof(objects) / sizeof(objects[0]), objects, false, INFINITE);
		switch(result) {
		case WAIT_OBJECT_0:
			reset();
			return;
		case WAIT_OBJECT_0 + 1:
		case WAIT_ABANDONED_0:
		case WAIT_ABANDONED_0 + 1:
			return;
		case WAIT_FAILED:
			throw_windows_error("WaitForMultipleObjects");
		default:
			assert(!"WaitForMultipleObject returned unexpected value");
			return;
		}
	}

	inline bool notify_addr_change_listener::changed()
	{
		auto result = WaitForSingleObject(wait_handle, 0);
		switch(result) {
		case WAIT_OBJECT_0:
			reset();
			return true;
		case WAIT_ABANDONED_0:
			return false;
		case WAIT_TIMEOUT:
			return FALSE;
		case WAIT_FAILED:
			throw_windows_error("WaitForSingleObject");
		default:
			assert(!"WaitForSingleObject returned unexpected value");
			return false;
		}
	}
}}
