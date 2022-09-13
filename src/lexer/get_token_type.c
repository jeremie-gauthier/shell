#include "lexer.h"
#include "lib_char.h"
#include <stdbool.h>
#include <stddef.h>

static inline bool is_operator(const char c)
{
	const char *operator= ft_strchr(OPERATORS, c);
	return operator!= NULL && * operator!= '\0';
}

static inline bool is_eof(const char c)
{
	return c == '\0';
}

enum e_token_type get_token_type(char c)
{
	if (ft_isspace(c))
		return Whitespace;
	if (is_operator(c))
		return Operator;
	if (ft_isgraph(c))
		return Word;
	if (is_eof(c))
		return End;
	return Unknown;
}
