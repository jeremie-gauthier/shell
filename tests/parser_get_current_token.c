#include <stdlib.h>
#include <string.h>
#include "CuTest.h"
#include "token.h"
#include "lexer.h"
#include "parser.h"

static t_parser getMockParser()
{
	const char *input = "cd directory";

	const size_t TOKENS_LEN = 2;
	t_token *mock_tokens = malloc(sizeof(t_token) * TOKENS_LEN);
	mock_tokens[0] = (t_token){ .type = Command, .value = "cd directory" };
	mock_tokens[1] = (t_token){ .type = End, .value = NULL };

	const t_lexer mock_lexer = {
		.input = input,
		.input_idx = strlen(input),
		.tokens_len = TOKENS_LEN,
		.tokens = mock_tokens,
		.tokens_cap = DEFAULT_TOKEN_LIST_CAPACITY,
		.has_error = false,
	};

	return (t_parser) { .lexer = &mock_lexer, .current_token = 0 };
}

static void TestParser_GetCurrentToken(CuTest *tc)
{
	const t_parser dummy_parser = getMockParser();
	const t_token expected = dummy_parser.lexer->tokens[dummy_parser.current_token];
	const size_t expected_current_tok = 0;

	const t_token token = get_current_token(&dummy_parser);

	// test values as it returns a copy
	CuAssertStrEquals(tc, expected.value, token.value);
	CuAssertIntEquals(tc, expected.type, token.type);
	CuAssertIntEquals(tc, expected_current_tok, dummy_parser.current_token);

	free((void *)dummy_parser.lexer->tokens);
}

CuSuite *ParserGetCurrentTokenGetSuite()
{
	CuSuite *suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestParser_GetCurrentToken);
	return suite;
}
