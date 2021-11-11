#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

static bool is_operator(const char c);
static bool is_eof(const char c);

enum e_token_type get_token_type(char c)
{
	if (isspace(c))
		return Whitespace;
	if (isalpha(c))
		return Word;
	if (is_operator(c))
		return Operator;
	if (isdigit(c))
		return Number;
	if (is_eof(c))
		return End;
	return Unknown;
}

static bool is_operator(const char c)
{
	return strchr(OPERATORS, c) != NULL;
}

static bool is_eof(const char c)
{
	return c == '\0';
}
