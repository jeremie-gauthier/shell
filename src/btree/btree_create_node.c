#include <stddef.h>
#include <stdlib.h>
#include "btree.h"

t_btree *btree_create_node(const void *data, const t_btree *left, const t_btree *right)
{
	t_btree *node = malloc(sizeof(t_btree));
	if (node == NULL)
		return (NULL);

	node->data = (void *)data;
	node->left = (t_btree *)left;
	node->right = (t_btree *)right;
	return (node);
}
