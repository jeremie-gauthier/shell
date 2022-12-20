#include "lib_mem.h"
#include "lib_vec.h"
#include <stdlib.h>

#include "token.h"
#include <stdio.h>
#include <string.h>

static void vec_resize(t_vec *vec, size_t size)
{
	void **items = malloc(sizeof(*items) * size);
	if (!items)
		return;
	ft_memcpy(items, vec->items, sizeof(vec->items) * vec->size);
	ft_memdel((void **)&vec->items);
	vec->items = items;
	vec->capacity = size;
}

/// @brief Append an item to the vector
/// @param vec The vector to append the item to
/// @param item The item to append to the vector
void vec_push(t_vec *vec, void *item)
{
	if (vec->size <= vec->capacity)
		vec_resize(vec, vec->capacity * 2);
	vec->items[vec->size++] = item;
}
