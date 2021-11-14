#include <stdlib.h>
#include "CuTest.h"
#include "token.h"
#include "lexer.h"

static void TestLexerOperator(CuTest *tc)
{
	t_lexer lexer = { .input = ">&1", .input_idx = 0 };
	t_token token = operator(&lexer);
	const char *const expected = ">&";
	const size_t expected_input_idx = 2;

	CuAssertTrue(tc, token.type == Redirection);
	CuAssertStrEquals(tc, expected, token.value);
	CuAssertIntEquals(tc, expected_input_idx, lexer.input_idx);
	free((void *)token.value);
}

static void TestLexerOperator_AmbiguousPipeOr(CuTest *tc)
{
	t_lexer lexer = { .input = "|||", .input_idx = 0 };
	t_token token = operator(&lexer);
	const char *const expected = "||";
	const size_t expected_input_idx = 2;

	CuAssertTrue(tc, token.type == Logical);
	CuAssertStrEquals(tc, expected, token.value);
	CuAssertIntEquals(tc, expected_input_idx, lexer.input_idx);
	free((void *)token.value);
}

static void TestLexerOperator_AmbiguousRedirection(CuTest *tc)
{
	t_lexer lexer = { .input = "><", .input_idx = 0 };
	t_token token = operator(&lexer);
	const char *const expected = ">";
	const size_t expected_input_idx = 1;

	CuAssertTrue(tc, token.type == Redirection);
	CuAssertStrEquals(tc, expected, token.value);
	CuAssertIntEquals(tc, expected_input_idx, lexer.input_idx);
	free((void *)token.value);
}


CuSuite *LexerRulesOperatorGetSuite()
{
	CuSuite *suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestLexerOperator);
	SUITE_ADD_TEST(suite, TestLexerOperator_AmbiguousPipeOr);
	SUITE_ADD_TEST(suite, TestLexerOperator_AmbiguousRedirection);
	return suite;
}
