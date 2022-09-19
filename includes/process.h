#ifndef PROCESS_H
#define PROCESS_H

#include "shell.h"
#include "token.h"
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
	enum e_token_type type;
} t_cmd;

t_cmd create_command(const char *path, char *const *argv, const size_t argc, enum e_token_type type);
const char *find_command(t_shell *const shell, const t_cmd command);

bool run_process(t_shell *const shell, const t_cmd command);

#endif
