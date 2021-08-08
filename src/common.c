/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:53:58 by sjamie            #+#    #+#             */
/*   Updated: 2021/08/08 17:54:01 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys_malloc.h"

t_malloc_data	g_malloc_data = {
		{NULL}, {NULL}, {NULL}, -1};

void	*malloc(size_t size)
{
	if (g_malloc_data.pagesize == -1)
		g_malloc_data.pagesize = getpagesize();
	if (size >= TINY_SIZE_START && size <= TINY_SIZE_END)
	{
		return (alloc_as_tiny(size));
	}
	else if (size >= SMALL_SIZE_START && size <= SMALL_SIZE_END)
	{
		return (alloc_as_small(size));
	}
	else if (size >= LARGE_SIZE_START)
	{
		return (alloc_as_large(size));
	}
	else
		return (NULL);
}

void	free(void *ptr)
{
	char	alloc_type;
	char	*tmp_arr;

	if (ptr == NULL)
		return ;
	ptr = ptr - 1;
	tmp_arr = (char *)(ptr);
	alloc_type = tmp_arr[0];
	if (alloc_type == TINE_CHAR)
		free_as_tiny(ptr);
	else if (alloc_type == SMALL_CHAR)
		free_as_small(ptr);
	else if (alloc_type == LARGE_CHAR)
		free_as_large(ptr);
}

void	*realloc(void *ptr, size_t size)
{
	if (!ptr)
		return (malloc(size));
	if (size <= 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!can_free(ptr - 1))
		return (NULL);
	free(ptr);
	return (malloc(size));
}

void	show_alloc_mem(void)
{
	uint64_t	total;

	total = 0;
	total += print_tiny_return_total();
	total += print_small_return_total();
	total += print_large_return_total();
	ft_putstr("Total : ");
	print_uint64_t(total);
	ft_putstr(" bytes\n");
}

void	show_alloc_mem_ex(char type, uint32_t zone_number,
						size_t zone_print_size, uint32_t zone_wight_size)
{
	if (zone_wight_size > 500)
		zone_wight_size = 500;
	if (zone_wight_size <= 0 || zone_wight_size > 65535)
		zone_wight_size = 65535;
	if (type == TINE_CHAR)
		print_zones_tiny(zone_number, zone_print_size, zone_wight_size);
	else if (type == SMALL_CHAR)
		print_zones_small(zone_number, zone_print_size, zone_wight_size);
	else if (type == LARGE_CHAR)
		print_zones_large(zone_number, zone_print_size, zone_wight_size);
	else
		ft_putstr("invalid char type\n");
}
