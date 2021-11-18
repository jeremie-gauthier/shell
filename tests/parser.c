#include <stdlib.h>
#include <string.h>
#include "CuTest.h"
#include "token.h"
#include "lexer.h"
#include "parser.h"

static t_lexer getMockParser()
{
	const char *input = "cd dir && touch file && echo 'lol' > file";

	const size_t TOKENS_LEN = 8;
	t_token *mock_tokens = malloc(sizeof(t_token) * TOKENS_LEN);
	mock_tokens[0] = (t_token){ .type = Command, .value = "cd dir " };
	mock_tokens[1] = (t_token){ .type = Logical, .value = "&&" };
	mock_tokens[2] = (t_token){ .type = Command, .value = "touch file " };
	mock_tokens[3] = (t_token){ .type = Logical, .value = "&&" };
	mock_tokens[4] = (t_token){ .type = Command, .value = "echo 'lol' " };
	mock_tokens[5] = (t_token){ .type = Redirection, .value = ">" };
	mock_tokens[6] = (t_token){ .type = Command, .value = "file" };
	mock_tokens[7] = (t_token){ .type = End, .value = NULL };

	const t_lexer mock_lexer = {
		.input = input,
		.input_idx = strlen(input),
		.tokens_len = TOKENS_LEN,
		.tokens = mock_tokens,
		.tokens_cap = DEFAULT_TOKEN_LIST_CAPACITY,
		.has_error = false,
	};

	return mock_lexer;
}

static t_btree *getExpectedBtree(const t_lexer *const lexer)
{
	t_btree *root = BTREE_CREATE_ONE(lexer->tokens[5]);

	// level 1
	t_btree *lv1_left = BTREE_CREATE_ONE(lexer->tokens[3]);
	t_btree *lv1_right = BTREE_CREATE_ONE(lexer->tokens[6]);

	// level 2
	t_btree *lv2_left = BTREE_CREATE_ONE(lexer->tokens[1]);
	t_btree *lv2_right = BTREE_CREATE_ONE(lexer->tokens[4]);

	// level 3
	t_btree *lv3_left = BTREE_CREATE_ONE(lexer->tokens[0]);
	t_btree *lv3_right = BTREE_CREATE_ONE(lexer->tokens[2]);

	root->left = lv1_left;
	root->right = lv1_right;

	lv1_left->left = lv2_left;
	lv1_left->right = lv2_right;

	lv2_left->left = lv3_left;
	lv2_left->right = lv3_right;

	return root;
}

static t_lexer getMockParserErrored()
{
	const char *input = "cd dir && touch file && echo 'lol' > file";

	const size_t TOKENS_LEN = 7;
	t_token *mock_tokens = malloc(sizeof(t_token) * TOKENS_LEN);
	mock_tokens[0] = (t_token){ .type = Command, .value = "cd dir " };
	mock_tokens[1] = (t_token){ .type = Logical, .value = "&&" };
	mock_tokens[2] = (t_token){ .type = Command, .value = "touch file " };
	mock_tokens[3] = (t_token){ .type = Logical, .value = "&&" };
	mock_tokens[4] = (t_token){ .type = Command, .value = "echo 'lol' " };
	mock_tokens[5] = (t_token){ .type = Redirection, .value = ">" };
	mock_tokens[6] = (t_token){ .type = Command, .value = "file" };

	const t_lexer mock_lexer = {
		.input = input,
		.input_idx = strlen(input),
		.tokens_len = TOKENS_LEN,
		.tokens = mock_tokens,
		.tokens_cap = DEFAULT_TOKEN_LIST_CAPACITY,
		.has_error = false,
	};

	return mock_lexer;
}

static void TestParser(CuTest *tc)
{
	const t_lexer dummy_lexer = getMockParser();
	const t_btree *expected_btree = getExpectedBtree(&dummy_lexer);

	const t_btree *btree = parse(&dummy_lexer);

	// level 0
	CuAssertStrEquals(tc, expected_btree->token.value, btree->token.value);
	CuAssertIntEquals(tc, expected_btree->token.type, btree->token.type);

	// level 1
	CuAssertStrEquals(tc, expected_btree->left->token.value, btree->left->token.value);
	CuAssertIntEquals(tc, expected_btree->left->token.type, btree->left->token.type);

	CuAssertStrEquals(tc, expected_btree->right->token.value, btree->right->token.value);
	CuAssertIntEquals(tc, expected_btree->right->token.type, btree->right->token.type);

	// level 2
	CuAssertStrEquals(tc, expected_btree->left->left->token.value, btree->left->left->token.value);
	CuAssertIntEquals(tc, expected_btree->left->left->token.type, btree->left->left->token.type);

	CuAssertStrEquals(tc, expected_btree->left->right->token.value, btree->left->right->token.value);
	CuAssertIntEquals(tc, expected_btree->left->right->token.type, btree->left->right->token.type);

	// level 3
	CuAssertStrEquals(tc, expected_btree->left->left->left->token.value, btree->left->left->left->token.value);
	CuAssertIntEquals(tc, expected_btree->left->left->left->token.type, btree->left->left->left->token.type);

	CuAssertStrEquals(tc, expected_btree->left->left->right->token.value, btree->left->left->right->token.value);
	CuAssertIntEquals(tc, expected_btree->left->left->right->token.type, btree->left->left->right->token.type);

	free((void *)dummy_lexer.tokens);
	btree_free((t_btree *)expected_btree);
	btree_free((t_btree *)btree);
}

static void TestParser_NoEnd(CuTest *tc)
{
	const t_lexer dummy_lexer = getMockParserErrored();

	const t_btree *btree = parse(&dummy_lexer);

	CuAssertPtrEquals(tc, NULL, (void *)btree);
	free((void *)dummy_lexer.tokens);
}

CuSuite *ParserGetSuite()
{
	CuSuite *suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestParser);
	SUITE_ADD_TEST(suite, TestParser_NoEnd);
	return suite;
}
