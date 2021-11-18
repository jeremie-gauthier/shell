#include "token.h"
#include "parser.h"

static bool is_operator_type(const t_token token);

/*
 **	Rule:
 **	expr: factor (OPERATOR factor*)*
 */

t_btree *expr(t_parser *parser)
{
	t_btree *node = factor(parser);
	t_token current_token = get_current_token(parser);

	while (is_operator_type(current_token))
	{
		if (!eat(parser, current_token.type))
		{
			btree_free((t_btree *)node);
			return NULL;
		}
		node = btree_create_node(current_token, node, factor(parser));
		current_token = get_current_token(parser);
	}
	return node;
}

static bool is_operator_type(const t_token token)
{
	const enum e_token_type type = token.type;

	return type == Redirection || type == Pipe || type == Separator || type == Logical;
}
