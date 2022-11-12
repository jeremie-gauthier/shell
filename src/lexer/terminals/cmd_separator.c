#include "lexer.h"

const char *cmd_separator(t_lexer *const lexer)
{
	while (lexer->current_char == COMMAND_SEPARATOR)
	{
		advance_lexer(lexer);
		skip_whitespace(lexer);
	}
	return NULL;
}
