#ifndef AST_H
#define AST_H

#include "token.h"

#define AST_CREATE_ONE(token) ast_create_node(token, NULL, NULL)

typedef struct s_ast
{
	struct s_ast *left;
	struct s_ast *right;
	t_token token;
} t_ast;

t_ast *ast_create_node(t_token token, const t_ast *left, const t_ast *right);
void ast_apply_prefix(t_ast *ast, void (*fn)(t_token));
void ast_free(t_ast *ast);

/*
 ** DEBUG
 */

void print_ast(t_ast *root);

#endif
