#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "lexer.h"
#include "parser.h"

int main(int argc, char **argv)
{
	(void)argc;
	printf("Hello world!\n");
	const t_lexer input_lexer = lexer(argv[1]);
	if (!input_lexer.tokens)
	{
		printf("Error: lexer failed\n");
		return EXIT_FAILURE;
	}

	if (input_lexer.has_error)
	{
		fprintf(stderr, "42sh: grammar error near `%c'\n", input_lexer.input[input_lexer.input_idx]);
		free_lexer((t_lexer *)&input_lexer);
		return EXIT_FAILURE;
	}
	print_tokens(input_lexer.tokens);

	// t_btree *ast = btree_create_node(
	// 	&input_lexer.tokens[0],
	// 	NULL,
	// 	NULL
	// );
	// printf("\tnode = %s\n", ((t_token *)ast->data)->value);
	// ast = btree_create_node(&input_lexer.tokens[1], ast, NULL);

	// printf("\tnode = %s\n", ((t_token *)ast->data)->value);
	// printf("\tnode = %s\n", ((t_token *)ast->left->data)->value);

	const t_btree *ast = parse(&input_lexer);
	print_btree((t_btree *)ast);

	free_lexer((t_lexer *)&input_lexer);
	return EXIT_SUCCESS;
}
