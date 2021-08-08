#include "ft_malloc.h"

static	int16_t	free_and_return_size(void *sys_pointer, void *ptr)
{
	int16_t	i;
	char	*tmp_arr;

	i = (int16_t)(ptr - sys_pointer);
	tmp_arr = (char*)sys_pointer;
	while (tmp_arr[i] == BUSY_CHAR)
	{
		tmp_arr[i] = FREE_CHAR;
		++i;
	}
	tmp_arr[i] = FREE_CHAR;
	++i;
	return (i);
}

static	void 	free_memory_in_block(void *sys_pointer, void *user_pointer, void *old_sys_pointer, void *old_user_pointer, void *ptr)
{
	int16_t	alloc_size;

	memory_write(user_pointer + 8, &alloc_size, 2);
	alloc_size -= free_and_return_size(sys_pointer, ptr);
	memory_write(&alloc_size, user_pointer + 8, 2);
	if (alloc_size == 0)
	{
		if (old_sys_pointer != NULL)
		{
			memory_write(old_sys_pointer, sys_pointer, 8);
			memory_write(old_user_pointer, user_pointer, 8);
		}
		if (sys_pointer == g_malloc_data.tiny.sys_start)
		{
			if (sys_pointer == g_malloc_data.tiny.sys_end)
			{
				g_malloc_data.tiny.sys_end = NULL;
				g_malloc_data.tiny.user_end = NULL;
			}
			memory_write(&g_malloc_data.tiny.sys_start, sys_pointer, 8);
			memory_write(&g_malloc_data.tiny.user_start, user_pointer, 8);
		}
		else if (sys_pointer == g_malloc_data.tiny.sys_end)
		{
			memory_write(&g_malloc_data.tiny.sys_end, &old_sys_pointer, 8);
			memory_write(&g_malloc_data.tiny.user_end, &old_user_pointer, 8);
		}
		munmap(sys_pointer, g_malloc_data.pagesize);
		munmap(user_pointer, g_malloc_data.pagesize);
	}
}

void			*free_as_tiny(void *ptr)
{
	uintptr_t	sys_pointer_offset;
	void 		*sys_pointer;
	uintptr_t	user_pointer_offset;
	void 		*user_pointer;
	void 		*old_sys_pointer;
	void 		*old_user_pointer;

	sys_pointer_offset = (uintptr_t) g_malloc_data.tiny.sys_start;
	user_pointer_offset = (uintptr_t) g_malloc_data.tiny.user_start;
	old_sys_pointer = NULL;
	old_user_pointer = NULL;
	while (user_pointer_offset != 0)
	{
		sys_pointer = (NULL) + sys_pointer_offset;
		user_pointer = (NULL) + user_pointer_offset;
		if (ptr > user_pointer && ptr < user_pointer + g_malloc_data.pagesize)
			free_memory_in_block(sys_pointer, user_pointer, old_sys_pointer, old_user_pointer, ptr);
		if (sys_pointer == g_malloc_data.tiny.sys_end)
			return (false);
		memory_write(&sys_pointer_offset, sys_pointer, 8);
		memory_write(&user_pointer_offset, user_pointer, 8);
		old_sys_pointer = sys_pointer;
		old_user_pointer = user_pointer;
	}
}