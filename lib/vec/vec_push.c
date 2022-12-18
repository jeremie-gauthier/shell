#include "lib_mem.h"
#include "lib_vec.h"
#include <stdlib.h>

/// @brief Append an item to the vector
/// @param vec The vector to append the item to
/// @param item The item to append to the vector
void vec_push(t_vec *vec, void *item)
{
	if (vec->size <= vec->capacity)
	{
		vec->items = ft_realloc(vec->items, vec->capacity * 2);
		if (!vec->items)
		{
			vec->capacity = 0;
			vec->size = 0;
			return;
		}
		vec->capacity *= 2;
	}

	vec->items[vec->size++] = item;
}
