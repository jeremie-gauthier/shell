#include "interpreter.h"
#include "ast.h"
#include "parser.h"
#include <stdbool.h>

#include <stdio.h>

static void visit(t_ast *node)
{
	if (node->token.type == Word)
		return word_visitor(node);
}

bool interpreter(t_parser *parser)
{
	printf("__INTERPRETER__\n");
	t_ast *ast = parse(parser);
	print_ast(ast);
	visit(ast);
	ast_free(ast);
	return true;
}
