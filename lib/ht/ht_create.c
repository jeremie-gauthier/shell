#include "lib_ht.h"
#include "lib_mem.h"
#include <stdlib.h>

t_ht *ht_create()
{
	t_ht *table = malloc((sizeof *table));
	if (!table)
		return NULL;

	table->size = HT_CAPACITY;
	table->count = 0;
	if (!(table->items = malloc(sizeof(*table->items) * HT_CAPACITY)))
	{
		ht_free(table);
		return NULL;
	}
	ft_bzero(table->items, sizeof(*table->items) * HT_CAPACITY);

	if (!(table->overflow_buckets = malloc(sizeof(*table->overflow_buckets) * HT_CAPACITY)))
	{
		ht_free(table);
		return NULL;
	}
	ft_bzero(table->overflow_buckets, sizeof(*table->overflow_buckets) * HT_CAPACITY);

	return table;
}
