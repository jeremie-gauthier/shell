#include "ast.h"
#include "parser.h"

// _cmd_ : _arg_<sup> + </ sup>
t_ast *parse_cmd(t_parser *const restrict parser)
{
	t_token current_token = parser->current_token;
	if (current_token.type == Word)
		eat(parser, Word);

	t_ast *node = AST_CREATE_ONE(current_token);

	while (parser->current_token.type == Word)
	{
		node->right = parse_cmd(parser);
		eat(parser, Word);
	}

	return node;
}
