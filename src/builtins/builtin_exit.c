#include "lib_str.h"
#include "process.h"
#include "shell.h"
#include <stdlib.h>

static unsigned char parse_arg(const char *const arg)
{
	if (!ft_strisnum(arg))
		return 0;
	return (unsigned char)ft_atoi(arg);
}

/*
 * exit [ n ]
 * Exit the shell with the exit status specified by an arithmetic expression n;
 * if none is specified, use the exit status from the last command executed.
 * An EOF condition will also cause the shell to exit, unless the IGNORE_EOF option is set.
 */
int builtin_exit(t_shell *const shell, const t_cmd command)
{
	if (command.argc > 2)
		return EXIT_FAILURE;

	shell->status = STOPPED;
	if (command.argc == 2)
		return parse_arg(command.argv[1]);
	return EXIT_SUCCESS;
}
