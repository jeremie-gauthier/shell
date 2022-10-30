#include "lib_arr.h"
#include "lib_ht.h"
#include "shell.h"

void sh_free(t_shell shell)
{
	const size_t env_size = ft_arr_len((char const **)shell.env);

	ft_arr_free(shell.env, env_size);
	ht_free(shell.cache.cmd);
	ht_free(shell.cache.global);
}
