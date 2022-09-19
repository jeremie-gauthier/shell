#ifndef LIB_HT_H
#define LIB_HT_H

#include <stdbool.h>
#include <stddef.h>

#define HT_CAPACITY 4096
#define NOT_OCCUPIED NULL
#define HT_HAS(item) ((item) != NULL)
#define HT_HAS_NOT(item) ((item) == NULL)

/*
 *	Hashtable item
 */
typedef struct s_ht_item
{
	char *key;
	char *value;
} t_ht_item;

typedef struct s_ht_lst
{
	t_ht_item *item;
	struct s_ht_lst *next;
} t_ht_lst;

/*
 *	Hashtable
 */
typedef struct s_ht
{
	t_ht_item **items;
	t_ht_lst **overflow_buckets;
	size_t size;
	size_t count;
} t_ht;

size_t ht_hash(char *str);
t_ht_item *ht_create_item(char *key, char *value);
t_ht *ht_create();
void ht_item_free(t_ht_item *item);
void ht_free(t_ht *table);

const char *ht_set(t_ht *table, char *key, char *value);
char *ht_get(t_ht *table, char *key);
bool ht_delete(t_ht *table, char *key);

t_ht_lst *ht_lst_insert(t_ht_lst *list, t_ht_item *item);
t_ht_item *ht_lst_remove(t_ht_lst *list);
void ht_lst_free(t_ht_lst *list);

// DEBUG

void print_search(t_ht *table, char *key);
void print_table(t_ht *table);

#endif
