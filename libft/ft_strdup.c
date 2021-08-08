/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:37:58 by sjamie            #+#    #+#             */
/*   Updated: 2019/09/10 20:38:00 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*string;
	size_t	i;

	i = 0;
	while (s1[i])
		i++;
	if ((string = malloc(i * sizeof(char) + 1)) == NULL)
		return (NULL);
	string[i] = '\0';
	while (i--)
		string[i] = s1[i];
	return (string);
}
