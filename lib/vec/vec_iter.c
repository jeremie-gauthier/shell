#include "lib_vec.h"

/// @brief Apply a custom function on a vector (mutable)
/// @param vec The vector to iter on
/// @param vec_iter_fn The function to run on every vector's items
void vec_iter(t_vec *vec, void (*vec_iter_fn)(void **))
{
	if (vec_iter_fn)
		for (size_t i = 0; i < vec->size; i++)
			vec_iter_fn(&vec->items[i]);
}
