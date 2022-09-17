#include "process.h"
#include <stddef.h>

t_cmd create_command(const char *path, char *const *argv, const size_t argc)
{
	return (t_cmd){
		.path = path,
		.argv = argv,
		.argc = argc,
	};
}
