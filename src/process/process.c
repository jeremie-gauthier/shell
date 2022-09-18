#include "process.h"
#include "lib_arr.h"
#include "lib_ht.h"
#include "lib_str.h"
#include "shell.h"
#include "token.h"
#include <stdbool.h>
#include <stddef.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>

char *get_cmd_from_path(char *env_path, char *cmd)
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

/*
 * Create a new process with fork() and run the command
 * inside the child process.
 */
bool run_process(t_shell *shell, const t_cmd command)
{
	pid_t pid;
	int status = 0;

	if ((pid = fork()) < 0)
		return false;
	if (pid == 0)
	{
		// TODO: check command type
		if (command.type == PathCommand)
		{
			char *env_path = ht_get(shell->cache, "PATH");
			char *path = get_cmd_from_path(env_path, (char *)command.path);
			if (execve(path, command.argv, shell->env) < 0)
			{
				ft_strdel(&path);
				return false;
			}
			ft_strdel(&path);
		}
		else
		{
			if (execve(command.path, command.argv, shell->env) < 0)
				return false;
		}
	}
	else
		wait(&status);
	return true;
}
