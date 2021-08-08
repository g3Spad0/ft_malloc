/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 20:47:37 by sjamie            #+#    #+#             */
/*   Updated: 2019/09/16 20:47:38 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *cnt))
{
	t_list	*first;
	t_list	*second;

	if (!lst || !f)
		return (NULL);
	second = f(lst);
	first = second;
	while (lst->next)
	{
		first->next = f(lst->next);
		first = first->next;
		lst = lst->next;
	}
	return (second);
}
