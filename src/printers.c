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
#include <stdio.h>

void	print_address(void *ptr)
{
	char	arr[100];

	sprintf(arr, "%p", ptr);
	ft_putstr(arr);
}

void	print_char_as_hex(char c)
{
	char	arr[100];

	sprintf(arr, "%02X", c);
	write(1, arr, 2);
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
