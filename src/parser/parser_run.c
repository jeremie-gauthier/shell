#include "parser.h"
#include "shell.h"

/*
 * Entry point of the parser
 */
t_ast *parser_run(const t_shell *const shell, t_parser *const parser)
{
	return parse_list(shell, parser);
}
