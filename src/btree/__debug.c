#include <stdio.h>
#include "btree.h"
#include "lexer.h"

void print_btree(t_btree *root)
{
	if (root == NULL)
		printf("btree root (null)\n");
	else
		btree_apply_prefix(root, print_token);
}
