/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 16:06:48 by sjamie            #+#    #+#             */
/*   Updated: 2019/09/08 16:06:49 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	num;
	size_t	ten;
	short	tmp;

	if (n == 0)
		return (ft_putchar_fd('0', fd));
	num = n;
	ten = 1;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num = -num;
	}
	while (num / ten)
		ten *= 10;
	ten /= 10;
	while (ten)
	{
		tmp = num / ten;
		ft_putchar_fd(tmp + 48, fd);
		num -= ten * tmp;
		ten /= 10;
	}
}
