#include "interpreter.h"
#include "ast.h"
#include "lib_mem.h"
#include "parser.h"
#include "process.h"
#include <stdbool.h>
#include <stdlib.h>

static bool visit(t_shell *shell, t_ast *node)
{
	bool ret = true;

	if (node->token.type == Word)
	{
		const t_cmd cmd = word_visitor(node);
		ret = run_process(shell, cmd);
		ft_memdel((void **)&cmd.argv);
		return ret;
	}
	return ret;
}

bool interpreter(t_shell *shell, t_parser *parser)
{
	bool ret = true;

	t_ast *ast = parser_run(parser);
	// print_ast(ast);

	ret = visit(shell, ast);
	ast_free(ast);
	return ret;
}
