#include "lib_ht.h"
#include "lib_mem.h"
#include "lib_str.h"

void ht_item_free(t_ht_item *item)
{
	if (item)
	{
		ft_strdel(&item->key);
		ft_strdel(&item->value);
		ft_memdel((void **)&item);
	}
}

void ht_free(t_ht *table)
{
	for (size_t i = 0; i < table->size; i++)
	{
		t_ht_item *item = table->items[i];
		ht_item_free(item);

		t_ht_lst *overflow_bucket = table->overflow_buckets[i];
		ht_lst_free(overflow_bucket);
	}

	ft_memdel((void **)&table->overflow_buckets);
	ft_memdel((void **)&table->items);
	ft_memdel((void **)&table);
}
