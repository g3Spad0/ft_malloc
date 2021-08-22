/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:03:57 by sjamie            #+#    #+#             */
/*   Updated: 2021/08/08 18:03:59 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys_malloc.h"

static	char	to_sixteenfold(char c)
{
	if (c >= 10)
	{
		return (c + 87);
	}
	else
	{
		return (c + 48);
	}
}

static	void	ft_sixteenfold(size_t num, char *rew)
{
	char	arr[16];
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!num)
		arr[i++] = 48;
	while (num)
	{
		arr[i++] = to_sixteenfold((char)(num % 16));
		num /= 16;
	}
	while (i)
		rew[j++] = arr[--i];
	rew[j] = 0;
}

void	print_address(void *ptr)
{
	char	arr[100];

	if (ptr == NULL)
	{
		ft_putstr("(null)");
	}
	else
	{
		ft_sixteenfold((size_t)ptr, arr);
		ft_putstr("0X0");
		ft_putstr(arr);
	}
}

void	print_char_as_hex(char c)
{
	char	arr[100];

	ft_sixteenfold(c, arr);
	ft_putstr(arr);
}

void	print_uint64_t(uint64_t n)
{
	uint64_t	num;
	uint64_t	ten;
	uint64_t	tmp;

	if (n == 0)
		return (ft_putchar('0'));
	num = n;
	ten = 1;
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
