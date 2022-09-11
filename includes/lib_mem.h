#ifndef LIB_MEM_H
#define LIB_MEM_H

#include <stddef.h>

typedef unsigned char byte;

void *ft_memcpy(void *dst, const void *src, size_t n);
void *ft_memset(void *str, const int c, size_t n);
void ft_bzero(void *s, size_t n);

#endif
