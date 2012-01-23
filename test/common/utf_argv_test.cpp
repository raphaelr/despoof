#include <UnitTest++.h>
#include <despoof/utf_argv.h>

using namespace std;
using despoof::utf_argv;

SUITE(utf_argv_test) {
	TEST(argc_zero_does_not_throw)
	{
		utf_argv uargv(0, nullptr);
		uargv.argv();
	}

	TEST(utf_conversion)
	{
		static const wchar_t test_wstr[] = L"юникод ☠ !";
		static const wchar_t *ptest_wstr = test_wstr;
		
		utf_argv uargv(1, &ptest_wstr);
		CHECK_EQUAL("\xd1\x8e\xd0\xbd\xd0\xb8\xd0\xba\xd0\xbe\xd0\xb4\x20\xe2\x98\xa0\x20\x21", uargv.argv()[0]);
	}

	TEST(multiple_args)
	{
		static const wchar_t one[] = L"юникод1";
		static const wchar_t two[] = L"юникод2";
		static const wchar_t *ptest_wstr[] = { one, two };

		utf_argv uargv(2, ptest_wstr);
		CHECK_EQUAL("\xd1\x8e\xd0\xbd\xd0\xb8\xd0\xba\xd0\xbe\xd0\xb4\x31", uargv.argv()[0]);
		CHECK_EQUAL("\xd1\x8e\xd0\xbd\xd0\xb8\xd0\xba\xd0\xbe\xd0\xb4\x32", uargv.argv()[1]);
	}
}
