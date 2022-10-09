#include "env.h"
#include "lib_arr.h"
#include "lib_ht.h"
#include "lib_mem.h"
#include "lib_str.h"
#include "shell.h"
#include <stdbool.h>
#include <stdlib.h>

bool load_env_to_cache(t_ht *cache, char **env)
{
	size_t i = 0;
	while (env[i])
	{
		const char **kv_pair = ft_strsplit(env[i], '=');
		if (!kv_pair)
			return false;
		ht_set(cache, kv_pair[0], kv_pair[1]);
		ft_arr_free((char **)kv_pair, ft_arr_len(kv_pair));
		i++;
	}
	return true;
}
