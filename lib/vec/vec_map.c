#include "lib_vec.h"

/// @brief Apply a custom function on a vector (immutable)
/// @param vec The vector to map on
/// @param vec_map_fn The predicate to run on every vector's items
/// @return A new vector resulting of the application of the vec_map_fn over vec
t_vec *vec_map(t_vec *vec, void *(*vec_map_fn)(void *))
{
	t_vec *new_vec = vec_create(vec->size);
	if (!new_vec)
		return NULL;

	for (size_t i = 0; i < vec->size; i++)
		vec_push(new_vec, vec_map_fn(vec->items[i]));
	return new_vec;
}
