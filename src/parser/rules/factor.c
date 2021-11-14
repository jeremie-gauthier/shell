#include "token.h"
#include "btree.h"
#include "parser.h"

#include <stdio.h> // del

/*
 **	Rule:
 **	factor: COMMAND
 */

t_btree *factor(t_parser *parser)
{
	printf("Rule: factor\n");
	t_token current_token = get_current_token(parser);

	if (eat(parser, Command))
	{
		t_btree *node = BTREE_CREATE_ONE(&current_token);
		printf("\tfactor node: %s\n", ((t_token *)node->data)->value);
		return node;
	}
	return NULL;
}
