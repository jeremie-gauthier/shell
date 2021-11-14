#include <stdlib.h>
#include "CuTest.h"
#include "token.h"
#include "lexer.h"

void TestLexerCommand(CuTest *tc)
{
	t_lexer lexer = {
		.input = "Hello world!",
		.input_idx = 0,
	};
	t_token token = command(&lexer);
	CuAssertTrue(tc, token.type == Command);
	CuAssertStrEquals(tc, "Hello world!", token.value);
	free((void *)token.value);
}

CuSuite *LexerRulesCommandGetSuite()
{
	CuSuite *suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestLexerCommand);
	return suite;
}
