#include "CuTest.h"
#include "token.h"
#include "lexer.h"

void TestLexerWord(CuTest *tc)
{
	t_lexer lexer = {
		.input = "Hello world!",
		.input_idx = 0,
	};
	t_token token = word(&lexer);
	CuAssertTrue(tc, token.type == Word);
	CuAssertStrEquals(tc, "Hello", token.value);
}

CuSuite *LexerRulesWordGetSuite()
{
	CuSuite *suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestLexerWord);
	return suite;
}
