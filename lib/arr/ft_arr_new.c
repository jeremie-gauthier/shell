#include "lib_mem.h"
#include <stddef.h>
#include <stdlib.h>

char **ft_arr_new(size_t size)
{
	char **arr = malloc(sizeof(*arr) * (size + 1));
	if (!arr)
		return NULL;

	ft_bzero(arr, size + 1);

	return arr;
}
