#include "lib_mem.h"
#include <stddef.h>

char *ft_strncpy(char *const dest, const char *restrict src, size_t n)
{
	char *str;

	str = dest;
	while (*src && n > 0)
	{
		*str++ = *src++;
		n--;
	}
	ft_bzero(str, n);
	return dest;
}
