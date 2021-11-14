#include <stdlib.h>
#include "CuTest.h"
#include "token.h"
#include "lexer.h"

static void TestLexerUnknown(CuTest *tc)
{
	t_lexer lexer = { .input = ">&1", .input_idx = 0 };
	t_token token = unknown(&lexer);
	const char *const expected = NULL;
	const size_t expected_input_idx = 1;

	CuAssertTrue(tc, token.type == Unknown);
	CuAssertStrEquals(tc, expected, token.value);
	CuAssertIntEquals(tc, expected_input_idx, lexer.input_idx);
	free((void *)token.value);
}

CuSuite *LexerRulesUnknownGetSuite()
{
	CuSuite *suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestLexerUnknown);
	return suite;
}
