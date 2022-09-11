#include "lib_mem.h"
#include <stddef.h>
#include <stdlib.h>

char *ft_strnew(const size_t size)
{
	char *str;

	if (!(str = (char *)malloc(sizeof(*str) * (size + 1))))
		return NULL;
	ft_bzero(str, size + 1);
	return str;
}
