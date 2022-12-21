#include "lib_arr.h"
#include "process.h"
#include "shell.h"
#include <stdlib.h>

int builtin_env(t_shell *const shell, const t_cmd *command)
{
	(void)command;
	ft_print_arr((const char **)shell->env);
	return EXIT_SUCCESS;
}
