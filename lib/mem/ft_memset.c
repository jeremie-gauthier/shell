#include "lib_mem.h"
#include <stdio.h>

void *ft_memset(void *str, const int c, size_t n)
{
	byte *p;

	p = (byte *)str;
	while (n-- > 0)
	{
		*p++ = (byte)c;
	}
	return str;
}