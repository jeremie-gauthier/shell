#include <stdio.h>
#include "CuTest.h"

CuSuite *LexerRulesCommandGetSuite();
CuSuite *LexerRulesOperatorGetSuite();
CuSuite *LexerRulesUnknownGetSuite();
CuSuite *LexerRulesWhitespaceGetSuite();
CuSuite *LexerGetTokenType();
CuSuite *Lexer();

void RunAllTests(void)
{
	CuString *output = CuStringNew();
	CuSuite *suite = CuSuiteNew();

	CuSuiteAddSuite(suite, LexerRulesCommandGetSuite());
	CuSuiteAddSuite(suite, LexerRulesOperatorGetSuite());
	CuSuiteAddSuite(suite, LexerRulesUnknownGetSuite());
	CuSuiteAddSuite(suite, LexerRulesWhitespaceGetSuite());
	CuSuiteAddSuite(suite, LexerGetTokenType());
	CuSuiteAddSuite(suite, Lexer());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

int main(void)
{
	RunAllTests();
	return 0;
}
