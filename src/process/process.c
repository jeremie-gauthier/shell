#include "process.h"
#include "lib_str.h"
#include "shell.h"
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>

/*
 * Create a new process with fork() and run the command
 * inside the child process.
 */
bool run_process(t_shell *const shell, const t_cmd command)
{
	pid_t pid;
	int status = 0;

	const char *path = find_command(shell, command);
	if ((pid = fork()) < 0)
		return false;
	if (pid == 0)
	{
		if (execve(path, command.argv, shell->env) < 0)
			return false;
	}
	else
		wait(&status);
	// print_table(shell->cache.cmd);

	return true;
}
