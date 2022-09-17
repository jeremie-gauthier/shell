#include "parser.h"

/*
 * Entry point of the parser
 */
t_ast *parser_run(t_parser *const restrict parser)
{
	return parse_cmd(parser);
}
