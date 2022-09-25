#include "ast.h"
#include "parser.h"
#include "shell.h"

// PARAM_EXPANSION is just alnum strings if no brackets are provided
// else, it parses everything between the brackets

// cmd: WORD (PARAM_EXPANSION* cmd*)
t_ast *parse_cmd(const t_shell *const shell, t_parser *const restrict parser)
{
	const t_token current_token = parser->current_token;
	if (IS_VALID_TOKEN(current_token.type, Word))
		eat(shell, parser, Word);

	t_ast *node = AST_CREATE_ONE(current_token);
	t_ast *const head = node;
	while (IS_VALID_TOKEN(parser->current_token.type, Word))
	{
		node->right = AST_CREATE_ONE(parser->current_token);
		node = node->right;
		eat(shell, parser, Word);
	}

	node = head;
	return node;
}
