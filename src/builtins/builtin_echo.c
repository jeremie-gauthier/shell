#include "lib_str.h"
#include "process.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

static const char *join_args(const size_t argc, char *const *argv)
{
	size_t len = 0;
	for (size_t i = 1; i < argc; i++)
	{
		if (argv[i])
			len += ft_strlen(argv[i]) + 1;
	}

	char *str = ft_strnew(len);
	if (!str)
		return NULL;

	len = 0;
	for (size_t i = 1; i < argc; i++)
	{
		if (!argv[i])
			continue;

		ft_strcpy(&str[len], argv[i]);
		len += ft_strlen(argv[i]);
		str[len] = ' ';
		len += 1;
	}
	str[len - 1] = '\0';
	return str;
}

int builtin_echo(t_shell *const shell, const t_cmd command)
{
	const char *str = join_args(command.argc, command.argv);
	if (!str)
		return EXIT_FAILURE;

	printf("%s\n", str);
	ft_strdel((char **)&str);
	shell->last_exit_status = EXIT_SUCCESS;
	return EXIT_SUCCESS;
}
