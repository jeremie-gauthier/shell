#include <stddef.h>
#include <editline/readline.h>
#include <stdio.h>
#include "shell.h"

static void initialize_readline()
{
	using_history();
	rl_bind_key('\t', rl_complete);
	rl_completer_quote_characters = "\"'";
	rl_attempted_completion_function = (CPPFunction *)command_completion;
}

static const char *rl_gets(void)
{
	const char *const line_read = readline("> ");

	if (line_read && *line_read)
		add_history(line_read);

	return line_read;
}

int shell(void)
{
	initialize_readline();
	while (1)
	{
		const char *line_read = rl_gets();
		printf("%s\n", line_read);
	}
	return 0;
}

