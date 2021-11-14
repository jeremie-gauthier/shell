#include <stdlib.h>
#include "CuTest.h"
#include "token.h"
#include "lexer.h"

static void TestLexerWhitespace(CuTest *tc)
{
	t_lexer lexer = { .input = "     >&1", .input_idx = 0 };
	t_token token = whitespace(&lexer);
	const char *const expected = NULL;
	const size_t expected_input_idx = 6;

	CuAssertTrue(tc, token.type == Whitespace);
	CuAssertStrEquals(tc, expected, token.value);
	CuAssertIntEquals(tc, expected_input_idx, lexer.input_idx);
	free((void *)token.value);
}

static void TestLexerWhitespace_None(CuTest *tc)
{
	t_lexer lexer = { .input = ">&1", .input_idx = 0 };
	t_token token = whitespace(&lexer);
	const char *const expected = NULL;
	const size_t expected_input_idx = 1;

	CuAssertTrue(tc, token.type == Whitespace);
	CuAssertStrEquals(tc, expected, token.value);
	CuAssertIntEquals(tc, expected_input_idx, lexer.input_idx);
	free((void *)token.value);
}


CuSuite *LexerRulesWhitespaceGetSuite()
{
	CuSuite *suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestLexerWhitespace);
	SUITE_ADD_TEST(suite, TestLexerWhitespace_None);
	return suite;
}
