#include <stddef.h>
#include "btree.h"

void btree_apply_prefix(t_btree *btree, void (*fn)(void *))
{
	if (btree == NULL)
		return;
	fn(btree->data);
	btree_apply_prefix(btree->left, fn);
	btree_apply_prefix(btree->right, fn);
}
