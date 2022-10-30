#include "lib_str.h"
#include "shell.h"
#include <limits.h>
#include <unistd.h>

char *get_current_dir_name()
{
	char *path = ft_strnew(PATH_MAX);
	if (!path)
		return NULL;

	if (!getcwd(path, PATH_MAX))
	{
		ft_strdel(&path);
		return NULL;
	}

	const char *dir = ft_strrchr(path, PATH_SEPARATOR);
	if (!dir)
		return path;

	const char *dir_name = ft_strdup(dir + 1);
	ft_strdel(&path);
	return (char *)dir_name;
}
