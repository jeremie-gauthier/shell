#include "env.h"
#include "lib_ht.h"
#include "shell.h"
#include <stdlib.h>

static void init_cache(t_cache *cache)
{
	if (!(cache->global = ht_create()))
		exit(EXIT_FAILURE);
	if (!(cache->cmd = ht_create()))
	{
		ht_free(cache->global);
		exit(EXIT_FAILURE);
	}
}

t_shell sh_create(char **env)
{
	t_shell shell;
	init_cache(&shell.cache);
	if (!(load_env_to_cache(shell.cache.global, env)))
	{
		sh_free(shell);
		exit(EXIT_FAILURE);
	}
	shell.status = STOPPED;
	shell.env = env;
	shell.last_exit_status = 0;
	return shell;
}
