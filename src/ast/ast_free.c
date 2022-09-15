#include "ast.h"
#include <stddef.h>
#include <stdlib.h>

void ast_free(t_ast *ast)
{
	if (ast == NULL)
		return;

	ast_free(ast->left);
	ast_free(ast->right);
	free(ast);
	ast = NULL;
}
