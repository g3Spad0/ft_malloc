/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 11:02:12 by sjamie            #+#    #+#             */
/*   Updated: 2019/09/07 11:02:13 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	unsigned char	*tmp_1;
	unsigned char	*tmp_2;
	size_t			i;

	i = 0;
	tmp_1 = (unsigned char *)dst;
	tmp_2 = (unsigned char *)src;
	while (i < n)
	{
		tmp_1[i] = tmp_2[i];
		i++;
	}
	return (dst);
}
