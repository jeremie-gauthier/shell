#include "env.h"
#include "lib_arr.h"
#include "lib_str.h"
#include <stddef.h>

char *env_set(char **env, const char *const key, const char *const value)
{
	char *env_var = ft_strjoin(key, value, "=");
	if (!env_var)
		return NULL;

	const int env_idx = env_get_idx(env, key);
	if (IS_ENV_SET(env_idx))
	{
		ft_strdel(&env[env_idx]);
		env[env_idx] = env_var;
	}
	else
		ft_arr_append(env, env_var);

	return env_var;
}
