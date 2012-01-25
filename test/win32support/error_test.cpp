#include <UnitTest++.h>
#include <despoof/win32/targetwindows.h>
#include <despoof/win32/error.h>

SUITE(error_test) {
	TEST(throw_windows_error_throws)
	{
		CHECK_THROW(throw_windows_error("function"), windows_error);
	}

	TEST(throw_windows_error_with_error_code_throws)
	{
		CHECK_THROW(throw_windows_error("function", 1), windows_error);
	}
}
