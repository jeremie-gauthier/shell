#include "ast.h"
#include "parser.h"
#include "shell.h"

#include <stdio.h>

// expr: WORD (OPERATOR cmd)*
t_ast *parse_expr(const t_shell *const shell, t_parser *const parser)
{
	t_ast *node = parse_cmd(shell, parser);

	while (IS_VALID_TOKEN(parser->current_token.type, CommandSeparator))
	{
		node = ast_create_node(parser->current_token, node, NULL);
		eat(shell, parser, CommandSeparator);
		node->right = parse_cmd(shell, parser);
	}

	return node;
}
