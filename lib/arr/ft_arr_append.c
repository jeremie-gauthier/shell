#include "lib_arr.h"
#include "lib_mem.h"
#include "lib_str.h"
#include <stdlib.h>

char **ft_arr_append(char **arr, const char *const item)
{
	if (!arr)
	{
		char **new_arr = ft_arr_new(1);
		new_arr[0] = ft_strdup(item);
		return new_arr;
	}

	const size_t size = ft_arr_len((char const **)arr);
	char **new_arr = ft_arr_new(size + 1);
	if (!new_arr)
		return NULL;

	ft_memcpy(new_arr, arr, sizeof(*arr) * size);
	new_arr[size] = ft_strdup(item);

	ft_memdel((void **)&arr);

	return new_arr;
}
