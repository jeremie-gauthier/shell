#include "lib_arr.h"
#include "lib_mem.h"
#include "lib_str.h"
#include <stdlib.h>

char **ft_arr_append(char **arr, const char *const item)
{
	const size_t size = ft_arr_len((char const **)arr);

	char **new_arr = malloc(sizeof(char *) * (size + 1));
	if (!new_arr)
		return NULL;

	ft_memcpy(new_arr, arr, sizeof(char *) * size);
	new_arr[size] = ft_strdup(item);
	new_arr[size + 1] = NULL;

	ft_memdel((void **)&arr);

	return new_arr;
}
