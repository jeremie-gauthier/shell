#include "lexer.h"

t_lexer lexer_create(const char *const restrict str)
{
	t_lexer lexer = {
		.input = str,
		.pos = 0,
		.current_char = str[0],
	};

	return lexer;
}
