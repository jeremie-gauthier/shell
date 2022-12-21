#include "ast.h"
#include "lib_mem.h"
#include "lib_str.h"
#include <stddef.h>
#include <stdlib.h>

static void free_expansion(void *expansion)
{
	t_expansion_token *token = expansion;
	ft_strdel(&token->parameter);
	ft_strdel(&token->substitution);
	ft_memdel((void **)&token);
}

static void free_word(void *word)
{
	t_word_token *token = word;
	ft_strdel(&token->text);
	ft_strdel(&token->substitution);
	vec_free(token->param_expansions, free_expansion);
	ft_memdel((void **)&word);
}

static void free_cmd(t_command_token *cmd)
{
	free_word(cmd->name);
	vec_free(cmd->suffix, free_word);
	ft_memdel((void **)&cmd);
}

void ast_free(t_ast *ast)
{
	if (ast == NULL)
		return;

	ast_free(ast->left);
	ast_free(ast->right);
	if (ast->token.type == Command)
		free_cmd(ast->token.command);
	else if (ast->token.type == Word)
		free_word(ast->token.word);
	ft_memdel((void **)&ast);
	ast = NULL;
}
