/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:03:57 by sjamie            #+#    #+#             */
/*   Updated: 2021/08/08 18:03:59 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys_malloc.h"

static	void	copy_as_large(void *ptr, void *new_ptr, size_t size)
{
	t_large_data	data;

	memory_write(&data, ptr - sizeof(t_large_data) - 1, sizeof(t_large_data));
	memory_write(new_ptr, ptr, (int) ft_min(size, data.real_size));
}

static	void	copy_as_small(void *ptr, void *new_ptr, size_t size)
{
	uint16_t	curr_size;

	memory_write(&curr_size, ptr - 2 - 1, 2);
	memory_write(new_ptr, ptr, (int) ft_min(size, curr_size));
}

static	void	tiny_copy(t_pair *data, void *ptr, void *new_ptr, size_t size)
{
	size_t	i;
	char	*arr;

	arr = (char *)data->sys_pointer;
	i = (size_t) (ptr - data->user_pointer);
	while (arr[i] == BUSY_CHAR)
		++i;
	++i;
	memory_write(new_ptr, ptr, (int) ft_min(size, i));
}

static	void	copy_as_tiny(void *ptr, void *new_ptr, size_t size)
{
	uintptr_t	sys_pointer_offset;
	uintptr_t	user_pointer_offset;
	t_pair		data;

	sys_pointer_offset = (uintptr_t) g_malloc_data.tiny.sys_start;
	user_pointer_offset = (uintptr_t) g_malloc_data.tiny.user_start;
	while (user_pointer_offset != 0)
	{
		data.sys_pointer = (void *)sys_pointer_offset;
		data.user_pointer = (void *)user_pointer_offset;
		if (ptr > data.user_pointer && ptr
		< data.user_pointer + g_malloc_data.pagesize)
			return (tiny_copy(&data, ptr, new_ptr, size));
		if (data.sys_pointer == g_malloc_data.tiny.sys_end)
			return ;
		memory_write(&sys_pointer_offset, data.sys_pointer, 8);
		memory_write(&user_pointer_offset, data.user_pointer, 8);
	}
}

void	*start_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	char	*tmp_arr;
	char	alloc_type;

	new_ptr = malloc(size);
	if (new_ptr == NULL)
		return (NULL);
	ft_bzero(new_ptr, size);
	tmp_arr = (char *)(ptr - 1);
	alloc_type = tmp_arr[0];
	if (alloc_type == TINE_CHAR)
		copy_as_tiny(ptr, new_ptr, size);
	else if (alloc_type == SMALL_CHAR)
		copy_as_small(ptr, new_ptr, size);
	else if (alloc_type == LARGE_CHAR)
		copy_as_large(ptr, new_ptr, size);
	start_free(ptr, FALSE);
	return (new_ptr);
}

