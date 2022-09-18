#include "process.h"
#include "token.h"
#include <stddef.h>

t_cmd create_command(const char *path, char *const *argv, const size_t argc, enum e_token_type type)
{
	return (t_cmd){
		.path = path,
		.argv = argv,
		.argc = argc,
		.type = type,
	};
}
