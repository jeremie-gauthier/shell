#ifndef SHELL_H
#define SHELL_H

#include "lib_ht.h"

enum e_shell_status
{
	STOPPED = 0,
	RUNNING
};

typedef struct shell
{
	char **env;
	t_ht *cache;
	enum e_shell_status status;
} t_shell;

t_shell sh_create(char **env);
int sh_run(t_shell shell);
void sh_free(t_shell shell);

#endif
