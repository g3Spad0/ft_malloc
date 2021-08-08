/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:28:22 by sjamie            #+#    #+#             */
/*   Updated: 2021/08/08 19:28:24 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys_malloc.h"

static	void	free_memory_in_block_norm(t_pair *data, void *old_sys_pointer,
						void *old_user_pointer)
{
	if (old_sys_pointer != NULL)
	{
		memory_write(old_sys_pointer, data->sys_pointer, 8);
		memory_write(old_user_pointer, data->user_pointer, 8);
	}
	if (data->sys_pointer == g_malloc_data.tiny.sys_start)
	{
		if (data->sys_pointer == g_malloc_data.tiny.sys_end)
		{
			g_malloc_data.tiny.sys_end = NULL;
			g_malloc_data.tiny.user_end = NULL;
		}
		memory_write(&g_malloc_data.tiny.sys_start, data->sys_pointer, 8);
		memory_write(&g_malloc_data.tiny.user_start, data->user_pointer, 8);
	}
	else if (data->sys_pointer == g_malloc_data.tiny.sys_end)
	{
		memory_write(&g_malloc_data.tiny.sys_end, &old_sys_pointer, 8);
		memory_write(&g_malloc_data.tiny.user_end, &old_user_pointer, 8);
	}
	munmap(data->sys_pointer, g_malloc_data.pagesize);
	munmap(data->user_pointer, g_malloc_data.pagesize);
}

static	int16_t	free_and_return_size(void *sys_pointer, void *ptr)
{
	int16_t	i;
	char	*tmp_arr;

	i = (int16_t)(ptr - sys_pointer);
	tmp_arr = (char *) sys_pointer;
	while (tmp_arr[i] == BUSY_CHAR)
	{
		tmp_arr[i] = FREE_CHAR;
		++i;
	}
	tmp_arr[i] = FREE_CHAR;
	++i;
	return (i);
}

static	void	free_memory_in_block(t_pair *data, void *old_sys_pointer,
									   void *old_user_pointer, void *ptr)
{
	int16_t	alloc_size;

	add_prompt(FREE_DONE_CHAR, ptr);
	memory_write(data->user_pointer + 8, &alloc_size, 2);
	alloc_size -= free_and_return_size(data->sys_pointer, ptr);
	memory_write(&alloc_size, data->user_pointer + 8, 2);
	if (alloc_size == 0)
	{
		free_memory_in_block_norm(data, old_sys_pointer, old_user_pointer);
	}
}

void	*free_as_tiny(void *ptr)
{
	uintptr_t	sys_pointer_offset;
	uintptr_t	user_pointer_offset;
	void		*old_sys_pointer;
	void		*old_user_pointer;
	t_pair		data;

	sys_pointer_offset = (uintptr_t) g_malloc_data.tiny.sys_start;
	user_pointer_offset = (uintptr_t) g_malloc_data.tiny.user_start;
	old_sys_pointer = NULL;
	old_user_pointer = NULL;
	while (user_pointer_offset != 0)
	{
		data.sys_pointer = (NULL) + sys_pointer_offset;
		data.user_pointer = (NULL) + user_pointer_offset;
		if (ptr > data.user_pointer && ptr
			< data.user_pointer + g_malloc_data.pagesize)
			free_memory_in_block(&data,
				old_sys_pointer, old_user_pointer, ptr);
		if (data.sys_pointer == g_malloc_data.tiny.sys_end)
			return (false);
		memory_write(&sys_pointer_offset, data.sys_pointer, 8);
		memory_write(&user_pointer_offset, data.user_pointer, 8);
		old_sys_pointer = data.sys_pointer;
		old_user_pointer = data.user_pointer;
	}
}
