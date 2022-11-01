#include "lib_str.h"
#include "shell.h"
#include <limits.h>
#include <unistd.h>

char *get_current_dir_name()
{
	char path[PATH_MAX];
	if (!getcwd(path, PATH_MAX))
		return NULL;

	const char *dir = ft_strrchr(path, PATH_SEPARATOR);
	if (!dir)
		return ft_strdup(path);
	return ft_strdup(dir + 1);
}
