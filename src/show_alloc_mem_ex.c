/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:16:20 by sjamie            #+#    #+#             */
/*   Updated: 2021/08/08 18:16:21 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys_malloc.h"

static	void	print_zone(size_t zone_print_size, uint32_t zone_wight_size,
							 char *zone, size_t real_zone_size)
{
	size_t	i;

	i = 0;
	while (i < zone_print_size && i < real_zone_size)
	{
		print_char_as_hex(zone[i]);
		if ((i + 1) % zone_wight_size == 0)
			ft_putstr("\n");
		else
			ft_putstr(" ");
		++i;
	}
	ft_putstr("\n");
}

static	void	print_zone_norm(size_t zone_print_size,
								  uint32_t zone_wight_size,
								  void *sys_pointer, void *user_pointer)
{
	ft_putstr("It is allocated area for system\n");
	print_zone(zone_print_size, zone_wight_size,
		sys_pointer, g_malloc_data.pagesize);
	ft_putstr("It is allocated area for user\n");
	print_zone(zone_print_size, zone_wight_size,
		user_pointer, g_malloc_data.pagesize);
}

void	print_zones_tiny(uint32_t zone_number, size_t zone_print_size,
						 uint32_t zone_wight_size)
{
	uintptr_t	sys_pointer_offset;
	void		*sys_pointer;
	uintptr_t	user_pointer_offset;
	void		*user_pointer;
	uint32_t	curr_number;

	curr_number = 1;
	sys_pointer_offset = (uintptr_t) g_malloc_data.tiny.sys_start;
	user_pointer_offset = (uintptr_t) g_malloc_data.tiny.user_start;
	while (user_pointer_offset != 0)
	{
		sys_pointer = (NULL) + sys_pointer_offset;
		user_pointer = (NULL) + user_pointer_offset;
		if (curr_number == zone_number)
		{
			print_zone_norm(zone_print_size, zone_wight_size,
				sys_pointer, user_pointer);
			return ;
		}
		if (sys_pointer == g_malloc_data.tiny.sys_end)
			break ;
		memory_write(&sys_pointer_offset, sys_pointer, 8);
		memory_write(&user_pointer_offset, user_pointer, 8);
	}
}

void	print_zones_small(uint32_t zone_number, size_t zone_print_size,
						  uint32_t zone_wight_size)
{
	uintptr_t	user_pointer_offset;
	void		*user_pointer;
	uint32_t	curr_number;

	curr_number = 1;
	user_pointer_offset = (uintptr_t) g_malloc_data.small.user_start;
	while (user_pointer_offset != 0)
	{
		user_pointer = (NULL) + user_pointer_offset;
		if (curr_number == zone_number)
		{
			print_zone(zone_print_size, zone_wight_size,
				user_pointer, g_malloc_data.pagesize * 3);
			return ;
		}
		if (user_pointer == g_malloc_data.small.user_end)
			break ;
		memory_write(&user_pointer_offset, user_pointer, 8);
	}
	ft_putstr("zone not found\n");
}

void	print_zones_large(uint32_t zone_number, size_t zone_print_size,
						  uint32_t zone_wight_size)
{
	uint32_t		curr_number;
	t_large_data	*data;

	curr_number = 1;
	data = g_malloc_data.large.start;
	while (data != NULL)
	{
		if (curr_number == zone_number)
		{
			print_zone(zone_print_size, zone_wight_size,
				(char*) data, data->mmap_size);
			return ;
		}
		data = data->next;
	}
	ft_putstr("zone not found\n");
}
