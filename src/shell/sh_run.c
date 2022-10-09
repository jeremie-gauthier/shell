#include "interpreter.h"
#include "lexer.h"
#include "lib_io.h"
#include "lib_str.h"
#include "parser.h"
#include "shell.h"
#include <stdio.h>

static void display_prompt()
{
	printf("$> ");
	fflush(stdout);
}

int sh_run(t_shell *const shell)
{
	char *input = NULL;

	shell->status = RUNNING;
	display_prompt();
	// signal(SIGINT, &sigint_core);
	while (shell->status == RUNNING && (input = readline(0)))
	{
		printf("received: %s\n", input);
		const t_lexer lexer = lexer_create(input);
		t_parser parser = parser_create(shell, lexer);
		interpreter(shell, &parser);

		ft_strdel(&input);
		if (shell->status == RUNNING)
			display_prompt();
	}
	free_readline_cache();
	return 0;
}
