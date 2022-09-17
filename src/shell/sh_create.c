#include "lib_ht.h"
#include "shell.h"
#include <stdlib.h>

t_shell sh_create(char **env)
{
	t_shell shell;

	shell.status = STOPPED;
	shell.env = env;
	if (!(shell.cache = ht_create()))
		exit(EXIT_FAILURE);
	return shell;
}
