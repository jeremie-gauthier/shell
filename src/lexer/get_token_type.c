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
	if (is_operator(c))
		return Operator;
	if (isgraph(c))
		return Command;
	if (is_eof(c))
		return End;
	return Unknown;
}

static bool is_operator(const char c)
{
	const char *operator = strchr(OPERATORS, c);
	return operator != NULL && *operator != '\0';
}

static bool is_eof(const char c)
{
	return c == '\0';
}
