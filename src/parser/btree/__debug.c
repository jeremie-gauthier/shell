#include <stdio.h>
#include "parser.h"

void print_btree(t_btree *root)
{
	if (root == NULL)
		printf("btree root (null)\n");
	else
		btree_apply_prefix(root, print_token);
}
