#ifndef SHELL_H
#define SHELL_H

#include "lib_ht.h"

#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif

enum e_shell_status
{
	STOPPED = 0,
	RUNNING
};

typedef struct s_cache
{
	t_ht *bin;
} t_cache;

typedef struct s_shell
{
	char **env;
	t_cache cache;
	enum e_shell_status status;
	unsigned char last_exit_status;
} t_shell;

t_shell sh_create(char **env);
int sh_run(t_shell *const shell);
void sh_free(t_shell shell);
char *get_current_dir_name();

#endif
