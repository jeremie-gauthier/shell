#include <stddef.h>
#include <stdlib.h>
#include "token.h"
#include "parser.h"

t_btree *btree_create_node(t_token token, const t_btree *left, const t_btree *right)
{
	t_btree *node = malloc(sizeof(t_btree));
	if (node == NULL)
		return NULL;

	node->token = token;
	node->left = (t_btree *)left;
	node->right = (t_btree *)right;
	return node;
}
