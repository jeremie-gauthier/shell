#ifndef PROCESS_H
#define PROCESS_H

#include "shell.h"
#include "token.h"
#include <stddef.h>
#include <unistd.h>

#define CHILD_PROCESS 0

typedef struct s_proc
{
	pid_t pid;
	unsigned char exit_status;
} t_proc;

enum e_command_type
{
	BuiltIn,
	Path,
	File,
};

/*
 * Store basic informations about the command to run.
 */
typedef struct s_cmd
{
	char *path;
	char **argv;
	size_t argc;
	enum e_command_type type;
} t_cmd;

// t_cmd create_command(const char *path, char *const *argv, const size_t argc, enum e_token_type type);
const char *find_command(t_shell *const shell, t_cmd *command);
int run_command(t_shell *const shell, const t_cmd *command);

int run_process(const char *const path, char *const *argv, char *const *env);

#endif
