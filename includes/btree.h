#ifndef BTREE_H
#define BTREE_H

#define BTREE_CREATE_ONE(data) btree_create_node(data, NULL, NULL)

typedef struct s_btree {
	struct s_btree *left;
	struct s_btree *right;
	void *data;
} t_btree;

t_btree *btree_create_node(const void *data, const t_btree *left, const t_btree *right);
void btree_apply_prefix(t_btree *btree, void (*fn)(void *));
void btree_free(t_btree *btree);

#endif
