#pragma once

#include <despoof/win32/targetwindows.h>
#include <despoof/win32/error.h>
#include <despoof/win32/abortable.h>

using namespace despoof::win32;

abortable::abortable()
	: event_(CreateEvent(NULL, true, false, NULL)), aborting_(false)
{
	if(!event_) {
		throw_windows_error("CreateEvent");
	}
}

void abortable::abort()
{
	if(!SetEvent(event_)) {
		throw_windows_error("SetEvent");
	}
	aborting_ = true;
}

void* abortable::wait_event()
{
	return event_;
}

bool abortable::aborting()
{
	return aborting_;
}
