#include "env.h"
#include "lib_arr.h"
#include "lib_ht.h"
#include "lib_str.h"
#include "shell.h"
#include <stdlib.h>

static void init_cache(t_cache *cache)
{
	if (!(cache->bin = ht_create()))
		exit(EXIT_FAILURE);
}

static char **init_env(char **env)
{
	const size_t size = ft_arr_len((char const **)env);

	char **dup_env = malloc(sizeof(char *) * (size + 1));
	if (!dup_env)
		return NULL;

	for (size_t i = 0; i < size; i++)
	{
		if (!(dup_env[i] = ft_strdup(env[i])))
		{
			ft_arr_free(dup_env, i);
			return NULL;
		}
	}
	dup_env[size] = NULL;

	return dup_env;
}

t_shell sh_create(char **env)
{
	t_shell shell;
	init_cache(&shell.cache);
	if (!(shell.env = init_env(env)))
	{
		sh_free(shell);
		exit(EXIT_FAILURE);
	}
	shell.status = STOPPED;
	shell.last_exit_status = 0;
	return shell;
}
