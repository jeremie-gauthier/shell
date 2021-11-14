#include <stddef.h>
#include <stdbool.h>
#include "parser.h"

const t_btree *parse(const t_lexer *const lexer)
{
	t_parser parser = { .lexer = lexer, .current_token = 0 };
	const t_btree *root = expr(&parser);
	const t_token current_token = get_current_token(&parser);

	if (current_token.type != End)
	{
		// free btree
		return NULL;
	}
	return root;
}

t_token get_current_token(const t_parser *const parser)
{
	return parser->lexer->tokens[parser->current_token];
}

static void advance(t_parser *const parser)
{
	parser->current_token++;
}

bool eat(t_parser *const parser, const enum e_token_type type)
{
	const t_token current_token = get_current_token(parser);

	if (current_token.type == type)
	{
		advance(parser);
		return true;
	}
	return false;
}
