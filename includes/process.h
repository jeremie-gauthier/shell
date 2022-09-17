#ifndef PROCESS_H
#define PROCESS_H

#include "shell.h"
#include <stdbool.h>
#include <stddef.h>

/*
 * Store basic informations about the command to run.
 */
typedef struct s_cmd
{
	const char *const path;
	char *const *argv;
	size_t argc;
} t_cmd;

t_cmd create_command(const char *path, char *const *argv, const size_t argc);

bool run_process(t_shell *shell, const t_cmd command);

#endif
