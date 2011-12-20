#pragma once

#include <despoof/win32/targetwindows.h>
#include <despoof/win32/error.h>
#include <despoof/win32/abortable.h>

using namespace despoof::win32;

abortable::abortable()
	: abort_pending_(false), abortable_(false)
{
	if(!DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(), &thread_, DUPLICATE_SAME_ACCESS, false, DUPLICATE_SAME_ACCESS)) {
		throw_windows_error("DuplicateHandle");
	}
}

void __stdcall abortable::apcproc(__w64 unsigned long self)
{
	reinterpret_cast<abortable*>(self)->abort_apc();
}

bool abortable::abort_pending()
{
	return abort_pending_;
}

void abortable::recognize_abort(bool value)
{
	abortable_ = value;
}

void abortable::abort_apc()
{
	if(!abortable_) {
		abort();
	}
}

void abortable::abort()
{
	abort_pending_ = true;
	QueueUserAPC(apcproc, thread_, reinterpret_cast<ULONG_PTR>(this));
}
