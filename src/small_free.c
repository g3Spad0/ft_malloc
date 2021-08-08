#include "ft_malloc.h"

static	void	final_free(void *user_pointer, void *curr_pointer,
					   int16_t curr_size, void *prev, void *old_user_pointer)
{
	int16_t			alloc_size;
	void			*next;

	memory_write(&alloc_size, user_pointer + 8, 2);
	alloc_size -= curr_size;
	memory_write(user_pointer + 8, &alloc_size, 2);
	if (alloc_size == 0)
	{
		memory_write(&next, user_pointer, 8);
		if (old_user_pointer != NULL)
			memory_write(old_user_pointer, user_pointer, 8);
		if (user_pointer == g_malloc_data.small.user_start)
		{
			if (user_pointer == g_malloc_data.small.user_end)
				g_malloc_data.small.user_end = NULL;
			memory_write(&g_malloc_data.small.user_start, user_pointer, 8);
		}
		else if (user_pointer == g_malloc_data.small.user_end)
		{
			memory_write(&g_malloc_data.small.user_end, &old_user_pointer, 8);
		}
		munmap(user_pointer, g_malloc_data.pagesize * 3);
	}
	else
	{
		memory_write(&next, curr_pointer, 8);
		memory_write(prev != NULL ? prev : user_pointer + 8 + 2, &next, 8);
	}
}

static	void	find_ptr_and_free(void *user_pointer, void *prt, void *old_user_pointer)
{
	void	*curr_pointer;
	void	*next;
	void	*prev;
	int16_t	curr_size;

	memory_write(&curr_pointer, user_pointer + 8 + 2, 8);
	prev = NULL;
	while (curr_pointer != NULL)
	{
		memory_write(&next, curr_pointer, 8);
		memory_write(&curr_size, curr_pointer + 8, 2);
		if (curr_pointer == prt)
		{
			final_free(user_pointer, curr_pointer, curr_size, prev, old_user_pointer);
		}
		prev = curr_pointer;
		curr_pointer = next;
	}
}

void			free_as_small(void *ptr)
{
	uintptr_t	user_pointer_offset;
	void 		*old_user_pointer;
	void 		*user_pointer;

	ptr -= 10;
	user_pointer_offset = (uintptr_t) g_malloc_data.small.user_start;
	old_user_pointer = NULL;
	while (user_pointer_offset != 0)
	{
		user_pointer = (NULL) + user_pointer_offset;
		if (user_pointer < ptr &&
			user_pointer + g_malloc_data.pagesize * 3 > ptr)
		{
			find_ptr_and_free(user_pointer, ptr, old_user_pointer);
			return ;
		}
		if (user_pointer == g_malloc_data.small.user_end)
			return ;
		memory_write(&user_pointer_offset, user_pointer, 8);
		old_user_pointer = user_pointer;
	}
}