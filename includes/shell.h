#ifndef SHELL_H
#define SHELL_H

#include "lib_ht.h"

enum e_shell_status
{
	STOPPED = 0,
	RUNNING
};

typedef struct s_cache
{
	t_ht *cmd;
	t_ht *global;
} t_cache;

typedef struct s_shell
{
	char *const *env;
	t_cache cache;
	enum e_shell_status status;
} t_shell;

t_shell sh_create(char **env);
int sh_run(t_shell shell);
void sh_free(t_shell shell);

#endif
