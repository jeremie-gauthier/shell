#ifndef LIB_ARR_H
#define LIB_ARR_H

#include <stddef.h>

void ft_print_arr(const char *const *const arr);
void ft_arr_free(char **arr, size_t size);
size_t ft_arr_len(char **arr);

#endif
