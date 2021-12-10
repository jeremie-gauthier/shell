#include <stddef.h>
#include <editline/readline.h>
#include <stdio.h>
#include "shell.h"
#include "interpreter.h"
#include "shellmod_rs.h"

static void initialize_readline()
{
	using_history();
	rl_bind_key('\t', rl_complete);
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
		const t_btree *node = parser(line_read);
		if (node)
			printf("read node from C: %s\n", node->token.value);
		print_btree((t_btree *)node);
		// interpreter(line_read);
	}
	return 0;
}

