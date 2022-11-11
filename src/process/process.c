#include "process.h"
#include "lib_str.h"
#include "shell.h"
#include "signals.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * Create a new process with fork() and run the command
 * inside the child process.
 */
int run_process(const char *const path, char *const *argv, char *const *env)
{
	int status = 0;

	if ((g_sig.current_proc.pid = fork()) < 0)
		return EXIT_FAILURE;
	if (g_sig.current_proc.pid == CHILD_PROCESS)
	{
		if (execve(path, argv, env) < 0)
			return EXIT_FAILURE;
	}
	else
		wait(&status);

	if (g_sig.signum > 0)
		return g_sig.current_proc.exit_status;
	return status;
}
