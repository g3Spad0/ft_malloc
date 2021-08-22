/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:21:51 by sjamie            #+#    #+#             */
/*   Updated: 2021/08/08 18:21:53 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys_malloc.h"
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

static	void	final_free_norm(void *next, t_small_norm *data)
{
	memory_write(&next, data->user_pointer, 8);
	if (data->old_user_pointer != NULL)
		memory_write(data->old_user_pointer, data->user_pointer, 8);
	if (data->user_pointer == g_malloc_data.small.user_start)
	{
		if (data->user_pointer == g_malloc_data.small.user_end)
			g_malloc_data.small.user_end = NULL;
		memory_write(&g_malloc_data.small.user_start,
			data->user_pointer, 8);
	}
	else if (data->user_pointer == g_malloc_data.small.user_end)
		memory_write(&g_malloc_data.small.user_end,
			&(data->old_user_pointer), 8);
	munmap(data->user_pointer, g_malloc_data.pagesize * 3);
}

static	void	final_free(t_small_norm *data)
{
	int16_t			alloc_size;
	void			*next;

	memory_write(&alloc_size, data->user_pointer + 8, 2);
	alloc_size -= data->curr_size;
	memory_write(data->user_pointer + 8, &alloc_size, 2);
	next = NULL;
	if (alloc_size == 0)
	{
		final_free_norm(next, data);
	}
	else
	{
		memory_write(&next, data->curr_pointer, 8);
		if (data->prev != NULL)
			memory_write(data->prev, &next, 8);
		else
			memory_write(data->user_pointer + 8 + 2, &next, 8);
	}
}

static	void	find_ptr_and_free(void *user_pointer, void *prt,
									void *old_user_pointer)
{
	void			*curr_pointer;
	void			*next;
	void			*prev;
	int16_t			curr_size;
	t_small_norm	data;

	memory_write(&curr_pointer, user_pointer + 8 + 2, 8);
	prev = NULL;
	while (curr_pointer != NULL)
	{
		memory_write(&next, curr_pointer, 8);
		memory_write(&curr_size, curr_pointer + 8, 2);
		if (curr_pointer == prt)
		{
			add_prompt(FREE_DONE_CHAR, curr_pointer + 8 + 2);
			data.user_pointer = user_pointer;
			data.curr_pointer = curr_pointer;
			data.curr_size = curr_size;
			data.prev = prev;
			data.old_user_pointer = old_user_pointer;
			final_free(&data);
		}
		prev = curr_pointer;
		curr_pointer = next;
	}
}

void	free_as_small(void *ptr)
{
	uintptr_t	user_pointer_offset;
	void		*old_user_pointer;
	void		*user_pointer;

	ptr -= 10;
	user_pointer_offset = (uintptr_t) g_malloc_data.small.user_start;
	old_user_pointer = NULL;
	while (user_pointer_offset != 0)
	{
		user_pointer = (void *)user_pointer_offset;
		if (user_pointer < ptr
			&& user_pointer + g_malloc_data.pagesize * 3 > ptr)
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
