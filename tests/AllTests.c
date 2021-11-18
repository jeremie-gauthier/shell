#include <stdio.h>
#include "CuTest.h"

CuSuite *LexerRulesCommandGetSuite();
CuSuite *LexerRulesOperatorGetSuite();
CuSuite *LexerRulesUnknownGetSuite();
CuSuite *LexerRulesWhitespaceGetSuite();
CuSuite *LexerGetTokenTypeGetSuite();
CuSuite *LexerGetSuite();

CuSuite *ParserEatGetSuite();
CuSuite *ParserGetCurrentTokenGetSuite();
CuSuite *ParserGetSuite();

void RunAllTests(void)
{
	CuString *output = CuStringNew();
	CuSuite *suite = CuSuiteNew();

	CuSuiteAddSuite(suite, LexerRulesCommandGetSuite());
	CuSuiteAddSuite(suite, LexerRulesOperatorGetSuite());
	CuSuiteAddSuite(suite, LexerRulesUnknownGetSuite());
	CuSuiteAddSuite(suite, LexerRulesWhitespaceGetSuite());
	CuSuiteAddSuite(suite, LexerGetTokenTypeGetSuite());
	CuSuiteAddSuite(suite, LexerGetSuite());

	CuSuiteAddSuite(suite, ParserEatGetSuite());
	CuSuiteAddSuite(suite, ParserGetCurrentTokenGetSuite());
	CuSuiteAddSuite(suite, ParserGetSuite());

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
