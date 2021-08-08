/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 18:46:52 by sjamie            #+#    #+#             */
/*   Updated: 2019/09/10 18:46:53 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;

	str = (NULL);
	while (*s)
	{
		if (*s == c)
			str = (char *)s;
		s++;
	}
	if (str)
		return (str);
	return (c == '\0' ? (char *)s : str);
}
