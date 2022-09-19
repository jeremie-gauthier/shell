#include "lib_mem.h"
#include "lib_str.h"

void ft_arr_free(char **arr, size_t size)
{
	size_t i = 0;
	while (i < size)
	{
		ft_strdel(&arr[i]);
		i++;
	}
	ft_memdel((void **)&arr);
}
