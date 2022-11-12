#include "interpreter.h"
#include "ast.h"
#include "lib_mem.h"
#include "parser.h"
#include "process.h"
#include "shell.h"
#include <stdlib.h>

#include <stdio.h>

static int visit(t_shell *const shell, t_ast *node)
{
	if (!node)
		return EXIT_FAILURE;

	if (node->token.type == Word)
	{
		const t_cmd cmd = word_visitor(node);
		shell->last_exit_status = (unsigned char)run_command(shell, cmd);
		ft_memdel((void **)&cmd.argv);
		return shell->last_exit_status;
	}
	if (node->token.type == CommandSeparator)
	{
		visit(shell, node->left);
		if (shell->status)
			return visit(shell, node->right);
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
