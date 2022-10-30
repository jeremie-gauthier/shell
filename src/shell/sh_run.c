#include "interpreter.h"
#include "lexer.h"
#include "lib_io.h"
#include "lib_str.h"
#include "parser.h"
#include "shell.h"
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

static void display_prompt()
{
	const char *path = get_current_dir_name();
	printf("\033[32;1m%s\033[0m ", path);
	fflush(stdout);
	ft_strdel((char **)&path);
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
