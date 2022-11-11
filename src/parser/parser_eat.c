#include "lexer.h"
#include "parser.h"
#include "shell.h"
#include "token.h"
#include <stdbool.h>

/*
 * Compare the current token type with the passed token
 * type and if they match then "eat" the current token
 * and assign the next token to the self.current_token.
 */
bool eat(const t_shell *const shell, t_parser *const parser, const enum e_token_type token_type)
{
	if (parser->current_token.type == token_type)
	{
		parser->current_token = get_next_token(shell, &parser->lexer);
		return true;
	}
	return false;
}
