/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:57:46 by sjamie            #+#    #+#             */
/*   Updated: 2021/08/08 17:57:47 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys_malloc.h"

size_t	get_large_offset(void)
{
	return (sizeof(t_large_data) + 1);
}

static	void	*alloc(t_large_data *data, size_t size)
{
	size_t	mmap_size;
	void	*p;

	mmap_size = get_large_offset() + size;
	if (mmap_size % g_malloc_data.pagesize != 0)
		mmap_size = (mmap_size / g_malloc_data.pagesize + 1)
			* g_malloc_data.pagesize;
	data->mmap_size = mmap_size;
	data->real_size = size;
	p = default_mmap(mmap_size);
	if (p == MAP_FAILED)
		return (NULL);
	return (p);
}

void	*alloc_as_large(size_t size)
{
	t_large_data	data;
	void			*p;

	p = alloc(&data, size);
	if (p == NULL)
		return (NULL);
	if (g_malloc_data.large.start == NULL)
	{
		data.prev = NULL;
		data.next = NULL;
		g_malloc_data.large.start = p;
		g_malloc_data.large.end = p;
	}
	else
	{
		data.prev = g_malloc_data.large.end;
		data.next = NULL;
		g_malloc_data.large.end->next = p;
		g_malloc_data.large.end = p;
	}
	memory_write(p, &data, sizeof(t_large_data));
	add_prompt(LARGE_CHAR, p + sizeof(t_large_data));
	return (p + get_large_offset());
}
