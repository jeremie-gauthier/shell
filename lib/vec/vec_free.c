#include "lib_mem.h"
#include "lib_vec.h"
#include <stdlib.h>

void vec_free(t_vec *vec, void (*vec_free_item)(void *))
{
	if (vec_free_item)
		for (size_t i = 0; i < vec->size; i++)
			vec_free_item(vec->items[i]);
	ft_memdel((void **)&vec->items);
	ft_memdel((void **)&vec);
}
