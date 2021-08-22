/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:16:33 by sjamie            #+#    #+#             */
/*   Updated: 2021/08/08 19:16:35 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys_malloc.h"

static	void	small_alloc(t_small_box *box, int16_t size)
{
	int16_t			alloc_size;
	int16_t			alloc_size_main;
	void			*curr_user_pointer;

	curr_user_pointer = box->user + box->offset;
	memory_write(box->user + box->offset, &box->next, 8);
	if (box->prev != NULL)
		memory_write(box->prev, &curr_user_pointer, 8);
	alloc_size = size + S_D_S;
	memory_write(curr_user_pointer + 8, &alloc_size, 2);
	add_prompt(SMALL_CHAR, curr_user_pointer + 8 + 2);
	if (box->prev == NULL)
		memory_write(box->user + 8 + 2, &curr_user_pointer, 8);
	box->user_offset = box->offset + S_D_S;
	memory_write(&alloc_size_main, box->user + 8, 2);
	alloc_size_main += alloc_size;
	memory_write(box->user + 8, &alloc_size_main, 2);
}

static	t_bool	new_alloc(t_small_box *box)
{
	void	*user;

	user = default_mmap(g_malloc_data.pagesize * 3);
	if (user == MAP_FAILED)
		return (FALSE);
	ft_bzero(user, g_malloc_data.pagesize * 3);
	if (g_malloc_data.small.user_start == NULL)
		g_malloc_data.small.user_start = user;
	else
		memory_write(g_malloc_data.small.user_end, &user, 8);
	g_malloc_data.small.user_end = user;
	box->user = user;
	box->prev = NULL;
	box->next = NULL;
	box->offset = SMALL_OFFSET;
	return (TRUE);
}

static	t_bool	set_if_find_zone(t_small_box *box, size_t size,
									 void *user_pointer, void *tmp)
{
	void		*curr_pointer;
	uint16_t	curr_size;
	t_bool		is_find;

	memory_write(&curr_pointer, user_pointer + 8 + 2, 8);
	if (is_in_start(box, size, user_pointer, curr_pointer))
		return (TRUE);
	while (curr_pointer != NULL)
	{
		memory_write(&tmp, curr_pointer, 8);
		memory_write(&curr_size, curr_pointer + 8, 2);
		if (tmp != NULL)
			is_find = tmp - curr_size - curr_pointer > to_ll(size + S_D_S);
		else
			is_find = user_pointer + g_malloc_data.pagesize * 3
				- curr_size - curr_pointer > to_ll(size + S_D_S);
		if (is_find)
		{
			set_norm(box, user_pointer, curr_pointer, tmp);
			box->offset = curr_pointer + curr_size - user_pointer;
			return (TRUE);
		}
		curr_pointer = tmp;
	}
	return (FALSE);
}

static	t_bool	find_free_zone(t_small_box *box, size_t size)
{
	uintptr_t	user_pointer_offset;
	void		*user_pointer;

	user_pointer_offset = (uintptr_t) g_malloc_data.small.user_start;
	while (TRUE)
	{
		user_pointer = (void *)user_pointer_offset;
		if (set_if_find_zone(box, size, user_pointer, NULL))
			return (TRUE);
		if (user_pointer == g_malloc_data.small.user_end)
			return (FALSE);
		memory_write(&user_pointer_offset, user_pointer, 8);
	}
}

void	*alloc_as_small(size_t size)
{
	t_small_box	box;

	if (g_malloc_data.small.user_end == NULL)
	{
		if (!new_alloc(&box))
			return (NULL);
		small_alloc(&box, (int16_t) size);
	}
	else
	{
		if (!find_free_zone(&box, size))
		{
			if (!new_alloc(&box))
				return (NULL);
		}
		small_alloc(&box, (int16_t) size);
	}
	return (box.user + box.user_offset);
}
