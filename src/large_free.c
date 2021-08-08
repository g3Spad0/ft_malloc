/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:57:22 by sjamie            #+#    #+#             */
/*   Updated: 2021/08/08 17:57:24 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys_malloc.h"

void	free_as_large(void *ptr)
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
	add_prompt(FREE_DONE_CHAR, ptr + sizeof(t_large_data));
	munmap(ptr, data.mmap_size);
}
