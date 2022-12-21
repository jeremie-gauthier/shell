#include "env.h"
#include "lib_arr.h"
#include "lib_mem.h"
#include "lib_str.h"
#include "process.h"
#include "shell.h"
#include <stdbool.h>
#include <stdlib.h>

static int replace_existing_env_var(char **existing_env_var, const char *const new_var)
{
	char *tmp = *existing_env_var;
	if (!(*existing_env_var = ft_strdup(new_var)))
	{
		*existing_env_var = tmp;
		return EXIT_FAILURE;
	}
	ft_strdel(&tmp);
	return EXIT_SUCCESS;
}

static bool is_valid_env_var(const char *env_var)
{
	size_t counter = 0;

	while (*env_var)
	{
		if (*env_var == '=')
			if (counter++ > 1)
				return false;
		env_var++;
	}
	return counter == 1;
}

int builtin_setenv(t_shell *const shell, const t_cmd *command)
{
	const char *env_var = command->argv[1];
	if (!is_valid_env_var(env_var))
		return EXIT_FAILURE;

	char const **kv_pair = ft_strsplit(env_var, '=');
	const size_t size_kv_pair = ft_arr_len(kv_pair);

	const char *key = kv_pair[0];
	const int idx = env_get_idx(shell->env, key);
	if (idx < 0)
	{
		ft_arr_free((char **)kv_pair, size_kv_pair);
		return EXIT_FAILURE;
	}

	if (shell->env[idx])
	{
		if (replace_existing_env_var(&shell->env[idx], env_var) == EXIT_FAILURE)
		{
			ft_arr_free((char **)kv_pair, size_kv_pair);
			return EXIT_FAILURE;
		}
	}
	else
	{
		if (!(shell->env = ft_arr_append(shell->env, env_var)))
		{
			ft_arr_free((char **)kv_pair, size_kv_pair);
			return EXIT_FAILURE;
		}
	}

	ft_arr_free((char **)kv_pair, size_kv_pair);

	return EXIT_SUCCESS;
}
