#include "env.h"
#include "lib_str.h"
#include "process.h"
#include "shell.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

int builtin_cd(t_shell *const shell, const t_cmd *command)
{
	char old_working_dir[PATH_MAX];
	if (!getcwd(old_working_dir, PATH_MAX))
		return EXIT_FAILURE;

	const char *path = command->argv[1];
	if (chdir(path) < 0)
		return EXIT_FAILURE;

	env_set(shell->env, "OLDPWD", old_working_dir);

	char new_working_dir[PATH_MAX];
	if (!getcwd(new_working_dir, PATH_MAX))
		return EXIT_FAILURE;
	env_set(shell->env, "PWD", new_working_dir);

	return EXIT_SUCCESS;
}
