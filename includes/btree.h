#ifndef BTREE_H
#define BTREE_H

#include "token.h" // del

#define BTREE_CREATE_ONE(token) btree_create_node(token, NULL, NULL)

typedef struct s_btree {
	struct s_btree *left;
	struct s_btree *right;
	t_token token;
} t_btree;

t_btree *btree_create_node(t_token token, const t_btree *left, const t_btree *right);
void btree_apply_prefix(t_btree *btree, void (*fn)(t_token));
void btree_free(t_btree *btree);

#endif
