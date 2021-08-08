/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:47:43 by sjamie            #+#    #+#             */
/*   Updated: 2021/08/08 17:47:46 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys_malloc.h"

static	void	tiny_alloc(t_tiny_box *box, size_t size)
{
	size_t	i;
	char	*arr;
	int16_t	alloc_size;

	i = 0;
	arr = (char *)(box->sys);
	while (i < size)
	{
		arr[i + box->offset] = BUSY_CHAR;
		++i;
	}
	arr[i - 1 + box->offset] = END_CHAR;
	add_prompt(TINE_CHAR, box->user + box->offset);
	memory_write(&alloc_size, box->user + 8, 2);
	alloc_size += size;
	memory_write(box->user + 8, &alloc_size, 2);
	box->user = box->user + box->offset + 1;
}

static	bool	new_alloc(t_tiny_box *box, void *user, void *sys)
{
	user = default_mmap(g_malloc_data.pagesize);
	if (user == MAP_FAILED)
		return (false);
	sys = default_mmap(g_malloc_data.pagesize);
	if (sys == MAP_FAILED)
		return (false);
	ft_bzero(sys, g_malloc_data.pagesize);
	ft_bzero(user, g_malloc_data.pagesize);
	if (g_malloc_data.tiny.user_start == NULL)
	{
		g_malloc_data.tiny.sys_start = sys;
		g_malloc_data.tiny.user_start = user;
	}
	else
	{
		memory_write(g_malloc_data.tiny.sys_end, &sys, 8);
		memory_write(g_malloc_data.tiny.user_end, &user, 8);
	}
	g_malloc_data.tiny.sys_end = sys;
	g_malloc_data.tiny.user_end = user;
	box->offset = TINY_OFFSET;
	box->user = g_malloc_data.tiny.user_start;
	box->sys = g_malloc_data.tiny.sys_start;
	return (true);
}

static	bool	set_if_find_zone(t_tiny_box *box, size_t size,
									void *sys_pointer, void *user_pointer)
{
	char		*arr;
	int			i;
	int			j;

	i = TINY_OFFSET;
	arr = (char *)sys_pointer;
	while (i < g_malloc_data.pagesize)
	{
		if (arr[i] == FREE_CHAR)
		{
			j = 0;
			while (arr[i] == FREE_CHAR && j < size)
			{
				++j;
				++i;
			}
			if (j == size)
				return (tiny_malloc_norm(box, sys_pointer,
						user_pointer, i - j));
			--i;
		}
		++i;
	}
	return (false);
}

static	bool	find_free_zone(t_tiny_box *box, size_t size)
{
	uintptr_t	sys_pointer_offset;
	void		*sys_pointer;
	uintptr_t	user_pointer_offset;
	void		*user_pointer;

	sys_pointer_offset = (uintptr_t) g_malloc_data.tiny.sys_start;
	user_pointer_offset = (uintptr_t) g_malloc_data.tiny.user_start;
	while (true)
	{
		sys_pointer = (NULL) + sys_pointer_offset;
		user_pointer = (NULL) + user_pointer_offset;
		if (set_if_find_zone(box, size, sys_pointer, user_pointer))
			return (true);
		if (sys_pointer == g_malloc_data.tiny.sys_end)
			return (false);
		memory_write(&sys_pointer_offset, sys_pointer, 8);
		memory_write(&user_pointer_offset, user_pointer, 8);
	}
}

void	*alloc_as_tiny(size_t size)
{
	t_tiny_box	box;

	size += 1;
	if (g_malloc_data.tiny.user_start == NULL)
	{
		if (!new_alloc(&box, NULL, NULL))
			return (NULL);
		tiny_alloc(&box, size);
	}
	else
	{
		if (!find_free_zone(&box, size))
		{
			if (!new_alloc(&box, NULL, NULL))
				return (NULL);
		}
		tiny_alloc(&box, size);
	}
	return (box.user);
}
