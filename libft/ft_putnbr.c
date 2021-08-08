/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:36:40 by sjamie            #+#    #+#             */
/*   Updated: 2019/09/07 16:36:41 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long	num;
	size_t	ten;
	short	tmp;

	if (n == 0)
		return (ft_putchar('0'));
	num = n;
	ten = 1;
	if (num < 0)
	{
		write(1, "-", 1);
		num = -num;
	}
	while (num / ten)
		ten *= 10;
	ten /= 10;
	while (ten)
	{
		tmp = num / ten;
		ft_putchar(tmp + 48);
		num -= ten * tmp;
		ten /= 10;
	}
}
