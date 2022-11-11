#include "shell.h"
#include "signals.h"
#include <signal.h>
#include <stdio.h>

void sigint(int signum)
{
	printf("\n");
	fflush(stdout);

	g_sig.signum = signum;
	if (g_sig.current_proc.pid)
	{
		g_sig.current_proc.exit_status = SIGINT_EXIT_CODE;
		kill(g_sig.current_proc.pid, signum);
	}
	else
		display_prompt();
}
