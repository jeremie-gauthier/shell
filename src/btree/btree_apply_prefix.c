#include <stddef.h>
#include "btree.h"

void btree_apply_prefix(t_btree *btree, void (*fn)(t_token))
{
	if (btree == NULL)
		return;
	fn(btree->token);
	btree_apply_prefix(btree->left, fn);
	btree_apply_prefix(btree->right, fn);
}
