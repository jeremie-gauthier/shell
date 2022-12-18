#include "lib_mem.h"
#include "lib_vec.h"
#include <stddef.h>
#include <stdlib.h>

/// @brief Create a new vector with desired capacity
/// @param capacity The memory capacity of this vec
/// @return A new, empty vector
t_vec *vec_create(const size_t capacity)
{
	t_vec *vec = malloc(sizeof(*vec));
	if (!vec)
		return NULL;

	if (!(vec->items = malloc(sizeof(*vec->items) * capacity)))
		return NULL;
	ft_bzero(vec->items, sizeof(*vec->items) * capacity);

	vec->capacity = capacity;
	vec->size = 0;
	return vec;
}
