#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	t_shell shell;

	shell = sh_create(env);
	// print_search(shell.cache, "PATH");
	sh_run(&shell);
	sh_free(shell);
	return shell.last_exit_status;
}
