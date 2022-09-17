#include "lib_char.h"
#include "CuTest.h"

static void TestFtIsAlnum(CuTest *tc)
{
	// valid cases
	CuAssertTrue(tc, ft_isalnum('a'));
	CuAssertTrue(tc, ft_isalnum('A'));
	CuAssertTrue(tc, ft_isalnum('z'));
	CuAssertTrue(tc, ft_isalnum('Z'));
	CuAssertTrue(tc, ft_isalnum('0'));
	CuAssertTrue(tc, ft_isalnum('9'));

	// invalid cases
	CuAssertFalse(tc, ft_isalnum('/'));
	CuAssertFalse(tc, ft_isalnum('('));
	CuAssertFalse(tc, ft_isalnum('"'));
	CuAssertFalse(tc, ft_isalnum('\0'));
	CuAssertFalse(tc, ft_isalnum('{'));
}

static void TestFtIsGraph(CuTest *tc)
{
	// valid cases
	CuAssertTrue(tc, ft_isgraph('a'));
	CuAssertTrue(tc, ft_isgraph('A'));
	CuAssertTrue(tc, ft_isgraph('z'));
	CuAssertTrue(tc, ft_isgraph('Z'));
	CuAssertTrue(tc, ft_isgraph('0'));
	CuAssertTrue(tc, ft_isgraph('9'));
	CuAssertTrue(tc, ft_isgraph(126));
	CuAssertTrue(tc, ft_isgraph(33));

	// invalid cases
	CuAssertFalse(tc, ft_isgraph(0));
	CuAssertFalse(tc, ft_isgraph(1));
	CuAssertFalse(tc, ft_isgraph(2));
	CuAssertFalse(tc, ft_isgraph(32));
	CuAssertFalse(tc, ft_isgraph(127));
	CuAssertFalse(tc, ft_isgraph(' '));
}

static void TestFtIsSpace(CuTest *tc)
{
	// valid cases
	CuAssertTrue(tc, ft_isspace(' '));
	CuAssertTrue(tc, ft_isspace('\t'));
	CuAssertTrue(tc, ft_isspace('\n'));
	CuAssertTrue(tc, ft_isspace('\r'));
	CuAssertTrue(tc, ft_isspace('\v'));
	CuAssertTrue(tc, ft_isspace('\f'));

	// invalid cases
	CuAssertFalse(tc, ft_isspace('\0'));
	CuAssertFalse(tc, ft_isspace('1'));
	CuAssertFalse(tc, ft_isspace('O'));
	CuAssertFalse(tc, ft_isspace('o'));
	CuAssertFalse(tc, ft_isspace(')'));
}

CuSuite *LibCharGetSuite()
{
	CuSuite *suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestFtIsAlnum);
	SUITE_ADD_TEST(suite, TestFtIsGraph);
	SUITE_ADD_TEST(suite, TestFtIsSpace);
	return suite;
}
