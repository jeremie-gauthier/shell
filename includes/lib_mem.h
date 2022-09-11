#ifndef LIB_MEM_H
#define LIB_MEM_H

#include <stddef.h>

typedef unsigned char byte;

void *ft_memcpy(void *dst, const void *src, size_t n);
void *ft_memset(void *str, const int c, size_t n);
void ft_bzero(void *s, size_t n);
size_t ft_memsize(void *ptr);
void ft_memdel(void **ap);
void *ft_realloc(void *src, const size_t size);

#endif
