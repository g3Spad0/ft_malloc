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

static	uint64_t	items_tiny_return_total(void *sys_pointer,
											  void *user_pointer,
											  int i, uint64_t total)
{
	char		*arr;
	int			j;

	arr = (char *)sys_pointer;
	while (i < g_malloc_data.pagesize)
	{
		if (arr[i] == BUSY_CHAR)
		{
			j = 0;
			while (arr[j + i] == BUSY_CHAR)
				++j;
			if (arr[j + i] == END_CHAR)
				j += 1;
			total += j;
			print_address(user_pointer + i + 1);
			ft_putstr(" - ");
			print_address(user_pointer + i + j);
			ft_putstr(" : ");
			print_uint64_t((uint64_t)(j - 1));
			ft_putstr(" bytes\n");
			i = j + i - 1;
		}
		++i;
	}
	return (total);
}

uint64_t	print_tiny_return_total(void)
{
	uintptr_t	sys_pointer_offset;
	void		*sys_pointer;
	uintptr_t	user_pointer_offset;
	void		*user_pointer;
	uint64_t	total;

	sys_pointer_offset = (uintptr_t) g_malloc_data.tiny.sys_start;
	user_pointer_offset = (uintptr_t) g_malloc_data.tiny.user_start;
	total = 0;
	while (user_pointer_offset != 0)
	{
		sys_pointer = (void *)sys_pointer_offset;
		user_pointer = (void *)user_pointer_offset;
		ft_putstr("TINY : ");
		print_address(user_pointer);
		ft_putstr("\n");
		total += items_tiny_return_total(sys_pointer, user_pointer,
				TINY_OFFSET, (uint64_t)0);
		if (sys_pointer == g_malloc_data.tiny.sys_end)
			break ;
		memory_write(&sys_pointer_offset, sys_pointer, 8);
		memory_write(&user_pointer_offset, user_pointer, 8);
	}
	return (total);
}

static	uint64_t	items_small_return_total(void *user_pointer)
{
	void		*curr_pointer;
	void		*next;
	int16_t		curr_size;
	uint64_t	total;

	total = 0;
	memory_write(&curr_pointer, user_pointer + 8 + 2, 8);
	while (curr_pointer != NULL)
	{
		memory_write(&next, curr_pointer, 8);
		memory_write(&curr_size, curr_pointer + 8, 2);
		print_address(curr_pointer + S_D_S);
		ft_putstr(" - ");
		print_address(curr_pointer + curr_size - S_D_S);
		ft_putstr(" : ");
		print_uint64_t((uint64_t)(curr_size - S_D_S));
		ft_putstr(" bytes\n");
		total += curr_size - S_D_S;
		curr_pointer = next;
	}
	return (total);
}

uint64_t	print_small_return_total(void)
{
	uintptr_t	user_pointer_offset;
	void		*user_pointer;
	uint64_t	total;

	user_pointer_offset = (uintptr_t) g_malloc_data.small.user_start;
	total = 0;
	while (user_pointer_offset != 0)
	{
		user_pointer = (void *)user_pointer_offset;
		ft_putstr("SMALL : ");
		print_address(user_pointer);
		ft_putstr("\n");
		total += items_small_return_total(user_pointer);
		if (user_pointer == g_malloc_data.small.user_end)
			break ;
		memory_write(&user_pointer_offset, user_pointer, 8);
	}
	return (total);
}

uint64_t	print_large_return_total(void)
{
	t_large_data	*data;
	uint64_t		total;

	data = g_malloc_data.large.start;
	total = 0;
	while (data != NULL)
	{
		ft_putstr("LARGE : ");
		print_address(data);
		ft_putstr("\n");
		print_address(data);
		ft_putstr(" - ");
		print_address(data + data->real_size);
		ft_putstr(" : ");
		print_uint64_t((uint64_t) data->real_size);
		ft_putstr(" bytes\n");
		total += data->real_size;
		data = data->next;
	}
	return (total);
}
