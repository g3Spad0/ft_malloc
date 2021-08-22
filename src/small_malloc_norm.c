/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_malloc_norm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:24:31 by sjamie            #+#    #+#             */
/*   Updated: 2021/08/08 19:24:34 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys_malloc.h"

t_bool	is_in_start(t_small_box *box, size_t size,
							  void *user_pointer, void *curr_pointer)
{
	if (curr_pointer - SMALL_OFFSET == user_pointer)
		return (FALSE);
	if (user_pointer + SMALL_OFFSET + size + S_D_S < curr_pointer)
	{
		box->user = user_pointer;
		box->prev = NULL;
		box->next = curr_pointer;
		box->offset = SMALL_OFFSET;
		return (TRUE);
	}
	return (FALSE);
}

void	set_norm(t_small_box *box, void *user_pointer,
					void *curr_pointer, void *tmp)
{
	box->user = user_pointer;
	box->prev = curr_pointer;
	box->next = tmp;
}

t_bool	tiny_malloc_norm(t_tiny_box *box, void *sys_pointer,
						 void *user_pointer, int v)
{
	box->sys = sys_pointer;
	box->user = user_pointer;
	box->offset = v;
	return (TRUE);
}
