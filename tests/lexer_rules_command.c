#include <stdlib.h>
#include "CuTest.h"
#include "token.h"
#include "lexer.h"

static void TestLexerCommand(CuTest *tc)
{
	t_lexer lexer = { .input = "Hello world!", .input_idx = 0 };
	t_token token = command(&lexer);
	const char *const expected = "Hello world!";
	const size_t expected_input_idx = 12;

	CuAssertTrue(tc, token.type == Command);
	CuAssertStrEquals(tc, expected, token.value);
	CuAssertIntEquals(tc, expected_input_idx, lexer.input_idx);
	free((void *)token.value);
}

static void TestLexerCommand_EmptyString(CuTest *tc)
{
	t_lexer lexer = { .input = "", .input_idx = 0 };
	t_token token = command(&lexer);
	const char *const expected = "";
	const size_t expected_input_idx = 0;

	CuAssertTrue(tc, token.type == Command);
	CuAssertStrEquals(tc, expected, token.value);
	CuAssertIntEquals(tc, expected_input_idx, lexer.input_idx);
	free((void *)token.value);
}

static void TestLexerCommand_TruncatedByOperator(CuTest *tc)
{
	t_lexer lexer = { .input = "Hello|world!", .input_idx = 0 };
	t_token token = command(&lexer);
	const char *const expected = "Hello";
	const size_t expected_input_idx = 5;

	CuAssertTrue(tc, token.type == Command);
	CuAssertStrEquals(tc, expected, token.value);
	CuAssertIntEquals(tc, expected_input_idx, lexer.input_idx);
	free((void *)token.value);
}

static void TestLexerCommand_WithSpaces(CuTest *tc)
{
	t_lexer lexer = { .input = "   HELLO   ", .input_idx = 0 };
	t_token token = command(&lexer);
	const char *const expected = "   HELLO   ";
	const size_t expected_input_idx = 11;

	CuAssertTrue(tc, token.type == Command);
	CuAssertStrEquals(tc, expected, token.value);
	CuAssertIntEquals(tc, expected_input_idx, lexer.input_idx);
	free((void *)token.value);
}


CuSuite *LexerRulesCommandGetSuite()
{
	CuSuite *suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestLexerCommand);
	SUITE_ADD_TEST(suite, TestLexerCommand_EmptyString);
	SUITE_ADD_TEST(suite, TestLexerCommand_TruncatedByOperator);
	SUITE_ADD_TEST(suite, TestLexerCommand_WithSpaces);
	return suite;
}
