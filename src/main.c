#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	t_shell shell;

	shell = create_shell(env);
	run_shell(shell);
	return EXIT_SUCCESS;
}
