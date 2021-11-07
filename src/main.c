#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "lexer.h"

int main(int argc, char **argv)
{
	(void)argc;
	printf("Hello world!\n");
	const t_token *tokens = lexer(argv[1]);
	print_tokens(tokens);
	free((void *)tokens);
	return 0;
}
