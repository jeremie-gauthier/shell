#include "lib_vec.h"

t_vec *vec_map(t_vec *vec, void *(*vec_map_fn)(void *))
{
	t_vec *new_vec = vec_create(vec->size);
	if (!new_vec)
		return NULL;

	for (size_t i = 0; i < vec->size; i++)
		vec_push(new_vec, vec_map_fn(vec->items[i]));
	return new_vec;
}
