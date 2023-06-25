#include "builtin.h"
#include "env.h"
#include "lib_arr.h"
#include "lib_ht.h"
#include "lib_str.h"
#include "process.h"
#include "token.h"
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

#include <stdio.h>
t_cmd create_command(const char *path, char *const *argv, const size_t argc, enum e_command_type type)
{
	return (t_cmd){
		.path = (char *)path,
		.argv = (char **)argv,
		.argc = argc,
		.type = type,
	};
}

static int can_access_file(const char *const path)
{
	return access(path, F_OK | X_OK) == 0;
}

static char *get_cmd_from_path(const char *const env_path, const char *const cmd)
{
	const char **paths = ft_strsplit(env_path, ':');
	size_t paths_len = ft_arr_len(paths);

	char *valid_path = NULL;
	size_t i = 0;
	while (paths[i] && !valid_path)
	{
		char *path = ft_strjoin(paths[i], cmd, "/");
		if (can_access_file(path))
		{
			valid_path = path;
			break;
		}
		ft_strdel(&path);
		i++;
	}
	ft_arr_free((char **)paths, paths_len);
	return valid_path;
}

const char *find_command(t_shell *const shell, t_cmd *command)
{
	if (command->type == Path)
	{
		const char *path = ht_get(shell->cache.bin, command->path);
		if (!path)
		{
			const char *env_path = env_get(shell->env, "PATH");
			if (!env_path)
				return NULL;
			if (!(path = get_cmd_from_path(env_path, command->path)))
				return NULL;

			const char *valid_path = ht_set(shell->cache.bin, command->path, path);
			ft_strdel(&command->path);
			command->path = (char *)valid_path;

			return command->path;
		}
		return path;
	}

	if (command->type == File && can_access_file(command->path))
		return command->path;

	return NULL;
}

int run_command(t_shell *const shell, const t_cmd *command)
{
	if (command->type == BuiltIn)
	{
		if (ft_strcmp(command->path, "exit") == SAME_STR)
			return builtin_exit(shell, command);
		if (ft_strcmp(command->path, "echo") == SAME_STR)
			return builtin_echo(shell, command);
		if (ft_strcmp(command->path, "env") == SAME_STR)
			return builtin_env(shell, command);
		if (ft_strcmp(command->path, "unsetenv") == SAME_STR)
			return builtin_unsetenv(shell, command);
		if (ft_strcmp(command->path, "setenv") == SAME_STR)
			return builtin_setenv(shell, command);
		if (ft_strcmp(command->path, "cd") == SAME_STR)
			return builtin_cd(shell, command);
	}

	const char *const path = find_command(shell, (t_cmd *)command);
	printf("command path = %s\n", path);
	if (!path)
		return false;

	return run_process(path, command->argv, shell->env);
}
