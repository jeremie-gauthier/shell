#include <stddef.h>
#include "token.h"
#include "parser.h"

/*
 **	Rule:
 **	factor: COMMAND
 */

t_btree *factor(t_parser *parser)
{
	t_token current_token = get_current_token(parser);

	if (eat(parser, Command))
		return BTREE_CREATE_ONE(current_token);
	return NULL;
}
