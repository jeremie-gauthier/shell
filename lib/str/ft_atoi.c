#include "lib_str.h"
#include <stddef.h>

int ft_atoi(const char *nptr)
{
	return (int)ft_strtol(nptr, NULL, 10);
}
