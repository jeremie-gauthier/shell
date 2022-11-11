#include "lib_str.h"
#include "shell.h"
#include <stdio.h>

void display_prompt()
{
	const char *path = get_current_dir_name();
	printf("\033[32;1m%s\033[0m ", path);
	fflush(stdout);
	ft_strdel((char **)&path);
}
