#include "ast.h"
#include "lib_mem.h"
#include "lib_str.h"
#include <stddef.h>
#include <stdlib.h>

void ast_free(t_ast *ast)
{
	if (ast == NULL)
		return;

	ast_free(ast->left);
	ast_free(ast->right);
	ft_strdel((char **)&ast->token.data);
	ft_memdel((void **)&ast);
	ast = NULL;
}
