/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:43:08 by sjamie            #+#    #+#             */
/*   Updated: 2021/08/08 17:43:12 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys_malloc.h"

void	memory_write(void *dst, void *src, int size)
{
	int		i;
	char	*c_dst;
	char	*c_src;

	c_dst = (char *)dst;
	c_src = (char *)src;
	i = 0;
	while (i < size)
	{
		c_dst[i] = c_src[i];
		i++;
	}
}

void	add_prompt(char type, void *src)
{
	char	*c_src;

	c_src = (char *)src;
	c_src[0] = type;
}

int	can_free(void *src)
{
	char	*c_src;
	char	c;

	c_src = (char *)src;
	c = c_src[0];
	return (c == TINE_CHAR || c == SMALL_CHAR || c == LARGE_CHAR);
}

void	*default_mmap(size_t size)
{
	return (mmap(0, size, PROT_READ | PROT_WRITE, \
			MAP_ANON | MAP_PRIVATE, -1, 0));
}

void	start_free(void *ptr, t_bool check_valid)
{
	char	alloc_type;
	char	*tmp_arr;

	if (ptr == NULL)
		return ;
	if (check_valid)
	{
		if (!can_free_pointer(ptr))
			return ;
		if (!can_free(ptr - 1))
			return ;
	}
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
