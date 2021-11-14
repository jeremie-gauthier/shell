#include "token.h"
#include "btree.h"
#include "parser.h"

#include <stdio.h> // del

static bool is_operator_type(const t_token token);

/*
 **	Rule:
 **	expr: factor (OPERATOR factor*)*
 */

t_btree *expr(t_parser *parser)
{
	printf("Rule: expr\n");
	// printf("CURRENT_TOKEN(1) = [%s (%s)]\n", get_current_token(parser).value, token_type_to_str(get_current_token(parser).type));
	t_btree *node = factor(parser);
	t_token current_token = get_current_token(parser);
	// printf("CURRENT_TOKEN(2) = [%s (%s)]\n", get_current_token(parser).value, token_type_to_str(get_current_token(parser).type));

	t_btree *tmp;
	while (is_operator_type(current_token))
	{
		// printf("CURRENT_TOKEN(3) = [%s (%s)]\n", get_current_token(parser).value, token_type_to_str(get_current_token(parser).type));
		if (!eat(parser, current_token.type))
		{
			// free btree
			return NULL;
		}
		// printf("CURRENT_TOKEN(4) = [%s (%s)]\n", get_current_token(parser).value, token_type_to_str(get_current_token(parser).type));
		// printf("CURRENT_TOKEN(5) = [%s (%s)]\n", get_current_token(parser).value, token_type_to_str(get_current_token(parser).type));
		// printf("cur_tok    = %p\n", &current_token);
		// printf("node->data = %p\n", node->data);

		// printf("\tfactor_node = %s\n", ((t_token *)factor_node->data)->value);
		// printf("\tnode = %s\n", ((t_token *)node->data)->value);
		// printf("\twill add current token = %s\n", ((t_token *)node->data)->value);
		tmp = node;
		node = BTREE_CREATE_ONE(&current_token);
		// node = btree_create_node((const void *)&current_token, node, NULL);
		node->left = tmp;
		t_btree *factor_node = factor(parser);
		node->right = factor_node;
		// printf("CURRENT_TOKEN(6) = [%s (%s)]\n", get_current_token(parser).value, token_type_to_str(get_current_token(parser).type));
		printf("\tfactor_node         = |%s|\n", ((t_token *)factor_node->data)->value);
		printf("\tfactor_node         = |%p|\n", ((t_token *)factor_node->data));
		printf("\tfactor_node in node = |%s|\n", ((t_token *)node->right->data)->value);
		printf("\tfactor_node in node = |%p|\n", ((t_token *)node->right->data));
		// printf("\tnode = %s\n", ((t_token *)node->data)->value);
		current_token = get_current_token(parser);
	}
	printf("No more operator type\n");
	printf("\tnode = %s (%s)\n", ((t_token *)node->data)->value, token_type_to_str(((t_token *)node->data)->type));
	// printf("\tnode = %s (%s)\n", ((t_token *)node->left->data)->value, token_type_to_str(((t_token *)node->left->data)->type));
	return node;
}

static bool is_operator_type(const t_token token)
{
	const enum e_token_type type = token.type;

	return type == Redirection || type == Pipe || type == Separator || type == Logical;
}
