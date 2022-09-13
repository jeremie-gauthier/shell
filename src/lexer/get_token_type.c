#include "lexer.h"
#include "lib_char.h"
#include "lib_str.h"
#include <stdbool.h>
#include <stddef.h>

static inline bool is_eof(const char c)
{
	return c == '\0';
}

enum e_token_type get_token_type(char c)
{
	if (ft_isgraph(c))
		return Word;
	if (is_eof(c))
		return End;
	return Unknown;
}
