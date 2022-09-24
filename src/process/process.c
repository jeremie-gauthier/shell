#include "process.h"
#include "lib_str.h"
#include "shell.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * Create a new process with fork() and run the command
 * inside the child process.
 */
int run_process(const char *const path, char *const *argv, char *const *env)
{
	pid_t pid;
	int status = 0;

	if ((pid = fork()) < 0)
		return EXIT_FAILURE;
	if (pid == CHILD_PROCESS)
	{
		if (execve(path, argv, env) < 0)
			return EXIT_FAILURE;
	}
	else
		wait(&status);
	return status;
}
