#ifndef SIGNALS_H
#define SIGNALS_H

#include "process.h"
#include <unistd.h>

#define SIGINT_EXIT_CODE 130

typedef struct s_sig
{
	t_proc current_proc;
	int signum;
} t_sig;

extern t_sig g_sig;

void sig_init(void);
void sigint(int signum);

#endif
