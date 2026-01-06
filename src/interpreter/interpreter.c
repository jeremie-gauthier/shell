#include "interpreter.h"
#include "ast.h"
#include "lib_mem.h"
#include "parser.h"
#include "process.h"
#include "shell.h"
#include <stdlib.h>

static int visit(t_shell *const shell, t_ast *node)
{
	if (!node)
		return EXIT_FAILURE;

	if (node->token.type == Command)
	{
		if (!subst_cmd_words(shell, node->token.command))
			return EXIT_FAILURE;
		const t_cmd *cmd = get_command_from_token(node->token.command);
		shell->last_exit_status = (unsigned char)run_command(shell, cmd);
		free_command(cmd);
		return shell->last_exit_status;
	}
	if (node->token.type == CommandSeparator)
	{
		visit(shell, node->left);
		if (shell->status)
			visit(shell, node->right);
		return shell->last_exit_status;
	}
	return EXIT_FAILURE;
}

int interpreter(t_shell *const shell, t_parser *parser)
{
	t_ast *ast = parser_run(shell, parser);
	// print_ast(ast);

	const int ret = visit(shell, ast);
	ast_free(ast);
	return ret;
}
