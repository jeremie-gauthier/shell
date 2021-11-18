#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "shell.h"

int main(int argc, char **argv)
{
	shell();

	(void)argc;
	printf("__LEXER__\n");
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

	printf("\n__PARSER__\n");
	const t_btree *ast = parse(&input_lexer);
	if (!ast)
	{
		printf("Error: parser failed\n");
		return EXIT_FAILURE;
	}

	print_btree((t_btree *)ast);

	free_lexer((t_lexer *)&input_lexer);
	return EXIT_SUCCESS;
}
