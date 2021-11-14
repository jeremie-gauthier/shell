#include <stddef.h>
#include <stdlib.h>
#include "btree.h"

#include "token.h" // del
#include <stdio.h> // del
#include <string.h> //del
#include <lexer.h> //del

t_btree *btree_create_node(const void *data, const t_btree *left, const t_btree *right)
{
	t_btree *node = malloc(sizeof(t_btree));
	if (node == NULL)
		return NULL;

	printf("inserting data: %s (%s)\n", ((t_token *)data)->value, token_type_to_str(((t_token *)data)->type));
	if (left)
	{
		printf("data = %p\n", data);
		printf("left = %p\n", left->data);
		printf("inserting left: %s\n", ((t_token *)left->data)->value);
	}
	node->data = (void *)data;
	// node->left = malloc(sizeof(t_btree));
	node->left = (t_btree *)left;
	if (left)
	{
		printf("\tassignation node->left = %s\n", ((t_token *)node->left->data)->value);
	}
	node->right = (t_btree *)right;
	return node;
}
