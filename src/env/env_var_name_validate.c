#include "env.h"
#include "lib_char.h"
#include <stdbool.h>

/*
 * An environment variable is considered valid if it respects
 * the following pattern:
 * [a-zA-Z_]{1,}[a-zA-Z0-9_]
 */
bool env_var_name_validate(const char *var)
{
	if (!ft_isalpha(*var) && *var != '_')
		return false;
	var++;
	while (*var)
	{
		if (!ft_isalnum(*var) && *var != '_')
			return false;
		var++;
	}
	return true;
}
