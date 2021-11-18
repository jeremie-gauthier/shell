#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "CuTest.h"
#include "token.h"
#include "lexer.h"

static void TestLexer(CuTest *tc)
{
	const char *input = "cd directory && touch file && echo 'Awesome shell' > file; echo hello | >&1";
	const t_lexer input_lexer = lexer(input);
	const size_t TOKENS_LEN = 13;
	const t_token expected_tokens[TOKENS_LEN] = {
		{.type = Command, .value = "cd directory "},
		{.type = Logical, .value = "&&"},
		{.type = Command, .value = "touch file "},
		{.type = Logical, .value = "&&"},
		{.type = Command, .value = "echo 'Awesome shell' "},
		{.type = Redirection, .value = ">"},
		{.type = Command, .value = "file"},
		{.type = Separator, .value = ";"},
		{.type = Command, .value = "echo hello "},
		{.type = Pipe, .value = "|"},
		{.type = Redirection, .value = ">&"},
		{.type = Command, .value = "1"},
		{.type = End, .value = NULL}
	};
	const t_lexer expected = {
		.input = input,
		.input_idx = strlen(input),
		.tokens_len = TOKENS_LEN,
		.tokens_cap = DEFAULT_TOKEN_LIST_CAPACITY,
		.has_error = false,
	};

	for (size_t i = 0; i < expected.tokens_len; i++)
	{
		CuAssertTrue(tc, input_lexer.tokens[i].type == expected_tokens[i].type);
		CuAssertStrEquals(tc, input_lexer.tokens[i].value, expected_tokens[i].value);
	}
	CuAssertTrue(tc, input_lexer.has_error == expected.has_error);
	CuAssertIntEquals(tc, expected.input_idx, input_lexer.input_idx);
	CuAssertIntEquals(tc, expected.tokens_len, input_lexer.tokens_len);
	CuAssertIntEquals(tc, expected.tokens_cap, input_lexer.tokens_cap);
	free_lexer((t_lexer *)&input_lexer);
}

static void TestLexer_EmptyString(CuTest *tc)
{
	const char *input = "";
	const t_lexer input_lexer = lexer(input);
	const t_token expected_tokens[1] = {
		{.type = End, .value = NULL}
	};
	const t_lexer expected = {
		.input = input,
		.input_idx = strlen(input),
		.tokens_len = 1,
		.tokens_cap = DEFAULT_TOKEN_LIST_CAPACITY,
		.has_error = false,
	};

	for (size_t i = 0; i < expected.tokens_len; i++)
	{
		CuAssertTrue(tc, input_lexer.tokens[i].type == expected_tokens[i].type);
		CuAssertStrEquals(tc, input_lexer.tokens[i].value, expected_tokens[i].value);
	}
	CuAssertTrue(tc, input_lexer.has_error == expected.has_error);
	CuAssertIntEquals(tc, expected.input_idx, input_lexer.input_idx);
	CuAssertIntEquals(tc, expected.tokens_len, input_lexer.tokens_len);
	CuAssertIntEquals(tc, expected.tokens_cap, input_lexer.tokens_cap);
	free_lexer((t_lexer *)&input_lexer);
}

CuSuite *LexerGetSuite()
{
	CuSuite *suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestLexer);
	SUITE_ADD_TEST(suite, TestLexer_EmptyString);
	return suite;
}
