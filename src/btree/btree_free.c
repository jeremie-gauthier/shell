#include <stddef.h>
#include <stdlib.h>
#include "btree.h"

void btree_free(t_btree *btree)
{
	if (btree == NULL)
		return;
	btree_free(btree->left);
	btree_free(btree->right);
	free(btree);
	btree = NULL;
}
