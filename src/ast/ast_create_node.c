#include "ast.h"
#include "token.h"
#include <stddef.h>
#include <stdlib.h>

t_ast *ast_create_node(t_token token, const t_ast *left, const t_ast *right)
{
	t_ast *node = malloc(sizeof(t_ast));
	if (node == NULL)
		return NULL;

	node->token = token;
	node->left = (t_ast *)left;
	node->right = (t_ast *)right;
	return node;
}
