/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:04:47 by sjamie            #+#    #+#             */
/*   Updated: 2021/08/08 18:04:48 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys_malloc.h"

static	t_bool	is_tiny_pointer(void *ptr)
{
	uintptr_t	sys_pointer_offset;
	void		*sys_pointer;
	uintptr_t	user_pointer_offset;
	void		*user_pointer;

	sys_pointer_offset = (uintptr_t) g_malloc_data.tiny.sys_start;
	user_pointer_offset = (uintptr_t) g_malloc_data.tiny.user_start;
	while (user_pointer_offset != 0)
	{
		sys_pointer = (void *)sys_pointer_offset;
		user_pointer = (void *)user_pointer_offset;
		if (user_pointer + 8 + 2 < ptr
			&& user_pointer + g_malloc_data.pagesize >= ptr)
		{
			return (TRUE);
		}
		if (sys_pointer == g_malloc_data.tiny.sys_end)
			break ;
		memory_write(&sys_pointer_offset, sys_pointer, 8);
		memory_write(&user_pointer_offset, user_pointer, 8);
	}
	return (FALSE);
}

static	t_bool	is_small_pointer(void *ptr)
{
	uintptr_t	user_pointer_offset;
	void		*user_pointer;

	user_pointer_offset = (uintptr_t) g_malloc_data.small.user_start;
	while (user_pointer_offset != 0)
	{
		user_pointer = (void *)user_pointer_offset;
		if (user_pointer + 8 + 2 + 8 < ptr
			&& user_pointer + g_malloc_data.pagesize * 3 > ptr)
		{
			return (TRUE);
		}
		if (user_pointer == g_malloc_data.small.user_end)
			break ;
		memory_write(&user_pointer_offset, user_pointer, 8);
	}
	return (FALSE);
}

static	t_bool	is_large_pointer(void *ptr)
{
	t_large_data	*data;
	void			*p;

	data = g_malloc_data.large.start;
	while (data != NULL)
	{
		p = ((void *)data) + get_large_offset();
		if (p == ptr)
		{
			return (TRUE);
		}
		data = data->next;
	}
	return (FALSE);
}

t_bool	can_free_pointer(void *ptr)
{
	if (is_tiny_pointer(ptr))
		return (TRUE);
	if (is_small_pointer(ptr))
		return (TRUE);
	if (is_large_pointer(ptr))
		return (TRUE);
	return (FALSE);
}

long long	to_ll(size_t size)
{
	return ((long long) size);
}
