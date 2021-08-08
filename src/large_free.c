#include "ft_malloc.h"

void			free_as_large(void *ptr)
{
	t_large_data	data;

	ptr -= sizeof(t_large_data);
	memory_write(&data, ptr, sizeof(t_large_data));
	if (data.mmap_size == 0)
		return ;
	if (data.prev == NULL)
	{
		g_malloc_data.large.start = data.next;
		if (data.next != NULL)
			data.next->prev = NULL;
	}
	else if (data.next == NULL)
	{
		g_malloc_data.large.end = data.prev;
		data.prev->next = NULL;
	}
	else
	{
		data.next->prev = data.prev;
		data.prev->next = data.next;
	}
	munmap(ptr, data.mmap_size);
}