#include "process.h"
#include "shell.h"
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * Create a new process with fork() and run the command
 * inside the child process.
 */
bool run_process(t_shell *shell, const t_cmd command)
{
	pid_t pid;
	int status = 0;

	if ((pid = fork()) < 0)
		return false;
	if (pid == 0)
	{
		if (execve(command.path, command.argv, shell->env) < 0)
			return false;
	}
	else
		wait(&status);
	return true;
}
