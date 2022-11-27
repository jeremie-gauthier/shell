#include "ast.h"
#include "parser.h"
#include "shell.h"

#include <stdio.h>

// list: WORD (OPERATOR cmd)*
t_ast *parse_list(const t_shell *const shell, t_parser *const parser)
{
	t_ast *node = parse_pipeline(shell, parser);

	while (IS_VALID_TOKEN(parser->current_token.type, CommandSeparator))
	{
		node = ast_create_node(parser->current_token, node, NULL);
		eat(shell, parser, CommandSeparator);
		node->right = parse_pipeline(shell, parser);
	}

	return node;
}
