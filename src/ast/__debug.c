#include "ast.h"
#include "token.h"
#include <stdio.h>

void print_ast(t_ast *root)
{
	if (root == NULL)
		printf("ast root (null)\n");
	else
		ast_apply_prefix(root, print_token);
}
