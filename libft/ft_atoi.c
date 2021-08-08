/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:02:15 by sjamie            #+#    #+#             */
/*   Updated: 2019/09/08 18:02:17 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	short	tmp;
	size_t	num;

	tmp = 1;
	num = 0;
	while (*str == '\n' || *str == '\t' || *str == '\v' ||
						*str == ' ' || *str == '\f' || *str == '\r')
		str++;
	if ((str[0] == '-' && str[1] == '+') || (str[0] == '+' && str[1] == '-'))
		return (0);
	if (*str == '-')
	{
		tmp = -tmp;
		str++;
	}
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		num = (num * 10) + (long long int)(*str++ - '0');
	return (num * tmp);
}
