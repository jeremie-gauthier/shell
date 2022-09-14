#include "shell.h"
#include "interpreter.h"
#include "lib_io.h"
#include "lib_str.h"
#include "parser.h"
#include <stddef.h>
#include <stdio.h>

t_shell create_shell()
{
	t_shell shell;

	shell.status = STOPPED;
	return shell;
}

void display_prompt()
{
	printf("$> ");
	fflush(stdout);
}

int run_shell(t_shell shell)
{
	char *input = NULL;

	shell.status = RUNNING;
	display_prompt();
	// signal(SIGINT, &sigint_core);
	while (shell.status == RUNNING && (input = readline(0)))
	{
		printf("received: %s\n", input);
		const t_lexer lexer = create_lexer(input);
		const t_parser parser = create_parser(lexer);
		print_token(parser.current_token);
		return 1;
		// print_tokens(lexer.tokens);
		// const t_btree *ast = parse(&lexer);
		// print_btree((t_btree *)ast);

		ft_strdel(&input);
		if (shell.status == RUNNING)
			display_prompt();
	}
	if (input && input[0] == 0)
		printf("\n");
	ft_strdel(&input);
	free_readline_cache();
	return 0;
}
