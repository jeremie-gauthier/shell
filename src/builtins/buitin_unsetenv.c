#include "env.h"
#include "lib_arr.h"
#include "lib_mem.h"
#include "lib_str.h"
#include "process.h"
#include "shell.h"
#include <stdlib.h>

#include <stdio.h>

int builtin_unsetenv(t_shell *const shell, const t_cmd command)
{
	const char *env_var = command.argv[1];
	const size_t idx = env_get_idx(shell->env, env_var);
	const size_t bytes_to_copy = sizeof(char *) * ft_arr_len((const char **)&shell->env[idx]);
	ft_memcpy(&shell->env[idx], &shell->env[idx + 1], bytes_to_copy);
	ht_delete(shell->cache.global, env_var);
	return EXIT_SUCCESS;
}
