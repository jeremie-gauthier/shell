#ifndef LIB_STR_H
#define LIB_STR_H

#include <stddef.h>

#define SAME_STR 0

char *ft_strchr(const char *str, int c);
char *ft_strrchr(const char *str, int c);
char *ft_strstr(const char *haystack, const char *needle);
int ft_strcmp(const char *s1, const char *s2);
int ft_strncmp(const char *s1, const char *s2, size_t n);
int ft_strncasecmp(const char *s1, const char *s2, size_t n);
size_t ft_strlen(const char *s);
char *ft_strnew(const size_t size);
void ft_strdel(char **const as);
char *ft_strdup(const char *const s);
char *ft_strndup(const char *const src, size_t n);
char *ft_strcpy(char *const dst, const char *src);
char *ft_strncpy(char *const dest, const char *src, size_t n);
char *ft_strjoin(const char *const s1, const char *const s2, const char *const junction);
void ft_strclr(char *s);
const char **ft_strsplit(char const *str, char c);
int ft_strisnum(const char *const str);
long int ft_strtol(const char *nptr, char **endptr, int base);
int ft_atoi(const char *nptr);

#endif
