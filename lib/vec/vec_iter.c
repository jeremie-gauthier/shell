#include "lib_vec.h"

void vec_iter(t_vec *vec, void (*vec_iter_fn)(void **))
{
	if (vec_iter_fn)
		for (size_t i = 0; i < vec->size; i++)
			vec_iter_fn(&vec->items[i]);
}
