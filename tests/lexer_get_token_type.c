#include <stdlib.h>
#include "CuTest.h"
#include "token.h"
#include "lexer.h"

static void TestLexerGetTokenType_Whitespace(CuTest *tc)
{
	CuAssertTrue(tc, get_token_type(' ') == Whitespace);
	CuAssertTrue(tc, get_token_type('\t') == Whitespace);
	CuAssertTrue(tc, get_token_type('\n') == Whitespace);
	CuAssertTrue(tc, get_token_type('\r') == Whitespace);
	CuAssertTrue(tc, get_token_type('\v') == Whitespace);
	CuAssertTrue(tc, get_token_type('\f') == Whitespace);
}

static void TestLexerGetTokenType_Operator(CuTest *tc)
{
	CuAssertTrue(tc, get_token_type('<') == Operator);
	CuAssertTrue(tc, get_token_type('>') == Operator);
	CuAssertTrue(tc, get_token_type('|') == Operator);
	CuAssertTrue(tc, get_token_type('&') == Operator);
	CuAssertTrue(tc, get_token_type(';') == Operator);
}

static void TestLexerGetTokenType_Command(CuTest *tc)
{
	CuAssertTrue(tc, get_token_type('a') == Command);
	CuAssertTrue(tc, get_token_type('A') == Command);
	CuAssertTrue(tc, get_token_type('!') == Command);
	CuAssertTrue(tc, get_token_type('1') == Command);
	CuAssertTrue(tc, get_token_type('(') == Command);
	CuAssertTrue(tc, get_token_type('"') == Command);
}

static void TestLexerGetTokenType_End(CuTest *tc)
{
	CuAssertTrue(tc, get_token_type('\0') == End);
}

CuSuite *LexerGetTokenType()
{
	CuSuite *suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestLexerGetTokenType_Whitespace);
	SUITE_ADD_TEST(suite, TestLexerGetTokenType_Operator);
	SUITE_ADD_TEST(suite, TestLexerGetTokenType_Command);
	SUITE_ADD_TEST(suite, TestLexerGetTokenType_End);
	return suite;
}
