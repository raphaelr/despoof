#include <UnitTest++.h>
#include <despoof/win32/targetwindows.h>
#include <despoof/win32/abortable.h>

using despoof::win32::abortable;

SUITE(abortable_test) {
	TEST(initial_state_is_not_aborting)
	{
		abortable ab;
		CHECK(!ab.aborting());
	}

	TEST(abort_changes_state_to_aborting)
	{
		abortable ab;
		ab.abort();
		CHECK(ab.aborting());
	}

	TEST(abort_event_is_not_set_initially)
	{
		abortable ab;
		CHECK_EQUAL(WAIT_TIMEOUT, WaitForSingleObject(ab.wait_event(), 0));
	}

	TEST(abort_event_is_set_after_aborting)
	{
		abortable ab;
		ab.abort();
		CHECK_EQUAL(WAIT_OBJECT_0, WaitForSingleObject(ab.wait_event(), 0));
	}
}
