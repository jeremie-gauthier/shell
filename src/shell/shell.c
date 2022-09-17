#include "shell.h"
#include "interpreter.h"
#include "lexer.h"
#include "lib_io.h"
#include "lib_str.h"
#include "parser.h"
#include "token.h"
#include <stddef.h>
#include <stdio.h>

t_shell create_shell()
{
	t_shell shell;

	shell.status = STOPPED;
	shell.env = NULL;
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
		t_parser parser = create_parser(lexer);
		interpreter(&shell, &parser);

		ft_strdel(&input);
		if (shell.status == RUNNING)
			display_prompt();
	}
	free_readline_cache();
	return 0;
}
