#include "lib_str.h"
#include <stddef.h>

size_t ft_strspn(const char *const restrict str, const char *const restrict accept)
{
	size_t len;

	len = 0;
	if (str && accept)
	{
		while (str[len])
		{
			if (!ft_strchr(accept, str[len]))
				return len;
			len++;
		}
	}
	return len;
}
