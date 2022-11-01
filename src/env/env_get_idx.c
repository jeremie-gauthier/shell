#include "lib_str.h"
#include <stddef.h>

int env_get_idx(char **env, const char *const key)
{
	size_t len_key = ft_strlen(key);
	int i = 0;

	while (env[i])
	{
		if (ft_strncmp(env[i], key, len_key) == SAME_STR && env[i][len_key] == '=')
			return i;
		i++;
	}
	return -1;
}
