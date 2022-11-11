#include "interpreter.h"
#include "lexer.h"
#include "lib_io.h"
#include "lib_str.h"
#include "parser.h"
#include "signals.h"
#include <limits.h>
#include <signal.h>
#include <unistd.h>

// #include <stdio.h>

t_sig g_sig;

int sh_run(t_shell *const shell)
{
	char *input = NULL;

	sig_init();
	signal(SIGINT, &sigint);

	shell->status = RUNNING;
	display_prompt();
	while (shell->status == RUNNING && (input = readline(0)))
	{
		// printf("received: %s\n", input);
		const t_lexer lexer = lexer_create(input);
		t_parser parser = parser_create(shell, lexer);
		interpreter(shell, &parser);

		ft_strdel(&input);
		if (shell->status == RUNNING)
			display_prompt();
		sig_init();
	}
	free_readline_cache();
	return 0;
}
