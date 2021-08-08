/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 14:29:19 by sjamie            #+#    #+#             */
/*   Updated: 2019/09/07 14:29:20 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_itoa_costil(void)
{
	char *string;

	if ((string = (char*)malloc(1 * sizeof(char) + 1)) == NULL)
		return (NULL);
	string[0] = '0';
	string[1] = '\0';
	return (string);
}

static	int		ft_itoa_fuck_norminette(long n)
{
	long	i;

	i = 0;
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	int		i;
	char	*string;
	long	zaebalo;

	if (n == 0)
		return (ft_itoa_costil());
	zaebalo = n;
	i = ft_itoa_fuck_norminette(zaebalo);
	if ((string = (char*)malloc(i * sizeof(char) + 1)) == NULL)
		return (NULL);
	if (zaebalo < 0)
	{
		string[0] = '-';
		zaebalo = -zaebalo;
	}
	string[i--] = '\0';
	while (zaebalo)
	{
		string[i] = zaebalo % 10 + 48;
		i--;
		zaebalo /= 10;
	}
	return (string);
}
