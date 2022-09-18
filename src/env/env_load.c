#include "env.h"
#include "lib_ht.h"
#include "lib_mem.h"
#include "lib_str.h"
#include "shell.h"
#include <stdbool.h>

bool load_env_to_cache(t_ht *cache, char **env)
{
	char **kv_pair;
	size_t i = 0;
	while (env[i])
	{
		if (!(kv_pair = ft_strsplit(env[i], '=')))
			return false;
		ht_set(cache, kv_pair[0], kv_pair[1]);
		ft_memdel((void **)&kv_pair);
		i++;
	}
	return true;
}
