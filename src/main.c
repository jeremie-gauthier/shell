#include "lexer.h"
#include "parser.h"
#include "shell.h"
#include "token.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib_str.h"
#include <string.h>

int testing_lexer_with_leaks(const char *input)
{
	printf("__LEXER__\n");
	const t_lexer input_lexer = lexer(input);
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

	btree_free((t_btree *)ast);
	free_lexer((t_lexer *)&input_lexer);
	return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_shell shell;

	shell = create_shell();
	run_shell(shell);
	// testing_lexer_with_leaks(argv[1]);

	// char *ret = ft_strslice(NULL, 2, 0);

	// str = ft_strstr("Le lion est mort ce soir", argv[1]);
	// printf(">>%s", ret);

	// while (1)
	// {
	// }
	return EXIT_SUCCESS;
}
