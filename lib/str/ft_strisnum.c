#include "lib_char.h"
#include <stddef.h>

int ft_strisnum(const char *const str)
{
	size_t i = 0;

	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return 0;
		i++;
	}
	return 1;
}
