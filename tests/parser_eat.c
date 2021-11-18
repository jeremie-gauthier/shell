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

static void TestParser_Eat(CuTest *tc)
{
	const t_parser dummy_parser = getMockParser();
	size_t expected_current_tok = 1;

	bool eat_result = eat((t_parser *const)&dummy_parser, Command);

	CuAssertIntEquals(tc, eat_result, true);
	CuAssertIntEquals(tc, expected_current_tok, dummy_parser.current_token);

	eat_result = eat((t_parser *const)&dummy_parser, Command);

	CuAssertIntEquals(tc, eat_result, false);
	CuAssertIntEquals(tc, expected_current_tok, dummy_parser.current_token);

	eat_result = eat((t_parser *const)&dummy_parser, End);
	expected_current_tok = 2;

	CuAssertIntEquals(tc, eat_result, true);
	CuAssertIntEquals(tc, expected_current_tok, dummy_parser.current_token);

	// always returns Unknown after End
	eat_result = eat((t_parser *const)&dummy_parser, Unknown);

	CuAssertIntEquals(tc, eat_result, true);
	CuAssertIntEquals(tc, expected_current_tok, dummy_parser.current_token);

	free((void *)dummy_parser.lexer->tokens);
}

CuSuite *ParserEatGetSuite()
{
	CuSuite *suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestParser_Eat);
	return suite;
}
