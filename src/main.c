#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "lexer.h"

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
	free_lexer((t_lexer *)&input_lexer);
	return EXIT_SUCCESS;
}
