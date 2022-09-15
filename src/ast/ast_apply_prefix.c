#include "ast.h"
#include "token.h"
#include <stddef.h>

void ast_apply_prefix(t_ast *ast, void (*fn)(t_token))
{
	if (ast == NULL)
		return;

	fn(ast->token);
	ast_apply_prefix(ast->left, fn);
	ast_apply_prefix(ast->right, fn);
}
