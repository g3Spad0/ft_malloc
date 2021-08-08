/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 19:12:32 by sjamie            #+#    #+#             */
/*   Updated: 2019/09/16 19:12:33 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*tmp;

	if (!alst && del)
		return ;
	while (*alst)
	{
		tmp = *alst;
		ft_lstdelone(alst, del);
		*alst = tmp->next;
	}
	*alst = NULL;
}
