#ifndef VEC_H
#define VEC_H

#include <stdbool.h>
#include <stddef.h>

typedef struct s_vec
{
	void **items;
	size_t capacity;
	size_t size;
} t_vec;

t_vec *vec_create(const size_t capacity);
void vec_free(t_vec *vec, void (*vec_free_item)(void *));
void vec_push(t_vec *vec, void *item);
void vec_iter(t_vec *vec, void (*vec_iter_fn)(void **));
t_vec *vec_map(t_vec *vec, void *(*vec_map_fn)(void *));

#endif
