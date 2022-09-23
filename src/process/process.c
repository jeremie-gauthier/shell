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
bool run_process(const char *const path, char *const *argv, char *const *env)
{
	pid_t pid;
	int status = 0;

	if ((pid = fork()) < 0)
		return false;
	if (pid == CHILD_PROCESS)
	{
		if (execve(path, argv, env) < 0)
			return false;
	}
	else
		wait(&status);
	return true;
}
