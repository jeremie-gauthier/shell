#include "lexer.h"
#include "lib_char.h"

void skip_whitespace(t_lexer *const lexer)
{
	while (lexer->current_char && ft_isspace(lexer->current_char))
		advance_lexer(lexer);
}
