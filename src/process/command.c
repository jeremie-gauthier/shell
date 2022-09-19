#include "lib_arr.h"
#include "lib_ht.h"
#include "lib_str.h"
#include "process.h"
#include "token.h"
#include <stddef.h>
#include <unistd.h>

#include <stdio.h>
t_cmd create_command(const char *path, char *const *argv, const size_t argc, enum e_token_type type)
{
	return (t_cmd){
		.path = path,
		.argv = argv,
		.argc = argc,
		.type = type,
	};
}

static char *get_cmd_from_path(const char *env_path, char *cmd)
{
	char **paths = ft_strsplit(env_path, ':');
	size_t paths_len = ft_arr_len(paths);

	char *valid_path = NULL;
	size_t i = 0;
	while (paths[i] && !valid_path)
	{
		char *pre_path = ft_strjoin(paths[i], "/");
		char *path = ft_strjoin(pre_path, cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			valid_path = path;
			ft_strdel(&pre_path);
			break;
		}
		ft_strdel(&pre_path);
		ft_strdel(&path);
		i++;
	}
	ft_arr_free(paths, paths_len);
	return valid_path;
}

const char *find_command(t_shell *const shell, const t_cmd command)
{
	// TODO: check command type
	if (command.type == PathCommand)
	{
		const char *path = ht_get(shell->cache.cmd, (char *)command.path);
		if (!path)
		{
			const char *env_path = ht_get(shell->cache.global, "PATH");
			path = get_cmd_from_path(env_path, (char *)command.path);
			const char *valid_path = ht_set(shell->cache.cmd, (char *)command.path, path);
			ft_strdel((char **)&path);
			return valid_path;
		}
		return path;
	}

	// If cmd is a file
	return command.path;
}
