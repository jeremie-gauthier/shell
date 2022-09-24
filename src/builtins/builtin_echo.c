#include "process.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int builtin_echo(t_shell *const shell, const t_cmd command)
{
	for (size_t i = 1; i < command.argc; i++)
	{
		if (i > 1)
			printf(" ");
		printf("%s", command.argv[i]);
	}
	printf("\n");
	shell->last_exit_status = EXIT_SUCCESS;
	return EXIT_SUCCESS;
}
