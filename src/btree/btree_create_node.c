#include <stddef.h>
#include <stdlib.h>
#include "btree.h"

#include "token.h" // del
#include <stdio.h> // del
#include <string.h> //del
#include <lexer.h> //del

t_btree *btree_create_node(t_token token, const t_btree *left, const t_btree *right)
{
	t_btree *node = malloc(sizeof(t_btree));
	if (node == NULL)
		return NULL;

	printf("inserting data: %s (%s)\n", token.value, token_type_to_str(token.type));
	if (left)
	{
		printf("data = %p\n", &token);
		printf("left = %p\n", &left->token);
		printf("inserting left: %s\n", left->token.value);
	}
	node->token = token;
	// node->left = malloc(sizeof(t_btree));
	node->left = (t_btree *)left;
	if (left)
	{
		printf("\tassignation node->left = %s\n", node->left->token.value);
	}
	node->right = (t_btree *)right;
	return node;
}
