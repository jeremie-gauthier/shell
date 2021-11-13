#include <stdbool.h>
#include "btree.h"
#include "parser.h"

#include <stdio.h> // del

const t_btree *parse(const t_lexer *const lexer)
{
	printf("\nBuilding parser...\n");
	t_parser parser = { .lexer = lexer, .current_token = 0 };
	printf("Building AST...\n");
	const t_btree *root = expr(&parser);
	printf("AST built.\n");
	printf("\tnode = %s\n", root->token.value);
	const t_token current_token = get_current_token(&parser);
	printf("Last token is %s expected End", token_type_to_str(current_token.type));
	if (current_token.type != End)
	{
		// free btree
		return NULL;
	}
	return root;
}

t_token get_current_token(const t_parser *const parser)
{
	// printf("cur_tok = %zu / %zu\n", parser->current_token, parser->lexer->tokens_len);
	// printf("%s\n", token_type_to_str(parser->lexer->tokens[parser->current_token].type));
	return parser->lexer->tokens[parser->current_token];
}

static void advance(t_parser *const parser)
{
	parser->current_token++;
}

bool eat(t_parser *const parser, const enum e_token_type type)
{
	const t_token current_token = get_current_token(parser);

	// printf("Eating %s expected %s\n", token_type_to_str(current_token.type), token_type_to_str(type));
	if (current_token.type == type)
	{
		advance(parser);
		return true;
	}
	return false;
}
