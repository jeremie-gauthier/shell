#include "lib_str.h"
#include <stddef.h>

char *env_get_value(char **env, char *key)
{
	size_t len_key = ft_strlen(key);
	size_t i = 0;

	while (env[i])
	{
		if (ft_strncmp(env[i], key, len_key) == SAME_STR)
			return &env[i][len_key + 1];
		i++;
	}
	return NULL;
}
