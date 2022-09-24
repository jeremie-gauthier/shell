#include "interpreter.h"
#include "ast.h"
#include "lib_mem.h"
#include "parser.h"
#include "process.h"
#include "shell.h"
#include <stdlib.h>

static int visit(t_shell *const shell, t_ast *node)
{
	if (node->token.type == Word)
	{
		const t_cmd cmd = word_visitor(node);
		shell->last_exit_status = run_command(shell, cmd);
		ft_memdel((void **)&cmd.argv);
		return shell->last_exit_status;
	}
	return EXIT_FAILURE;
}

int interpreter(t_shell *const shell, t_parser *parser)
{
	t_ast *ast = parser_run(parser);
	// print_ast(ast);

	const int ret = visit(shell, ast);
	ast_free(ast);
	return ret;
}
