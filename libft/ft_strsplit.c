/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:10:47 by sjamie            #+#    #+#             */
/*   Updated: 2019/09/07 12:10:48 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	**ft_strsplit_array(char const *str, char c)
{
	int count;
	int i;

	count = 0;
	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			while (str[i] != c && str[i] != '\0')
				i++;
			count++;
			continue ;
		}
		i++;
	}
	if (!count)
		return (NULL);
	return ((char**)malloc(count * sizeof(char*) + 1));
}

static	char	**ft_strsplit_fucking_norminette(void)
{
	char	**fuck_norminette;

	fuck_norminette = (char**)malloc(sizeof(char));
	if (fuck_norminette == NULL)
		return (NULL);
	*fuck_norminette = NULL;
	return (fuck_norminette);
}

static	char	*ft_strsplit_fuck_norminette(char const *str,
	int i, int z, char c)
{
	int		j;
	char	*string;

	if ((string = (char*)malloc((z - i) * sizeof(char) + 1)) == NULL)
		return (NULL);
	j = 0;
	while (str[i] != c && str[i] != '\0')
	{
		string[j] = str[i];
		i++;
		j++;
	}
	string[j] = '\0';
	return (string);
}

char			**ft_strsplit(char const *str, char c)
{
	int		i;
	int		j;
	int		k;
	char	**array;

	if (!str || !c)
		return (NULL);
	i = 0;
	k = 0;
	if ((array = ft_strsplit_array(str, c)) == NULL)
		return (ft_strsplit_fucking_norminette());
	while (str[i] && (j = i) >= 0)
	{
		if (str[i] != c)
		{
			while (str[j] != c && str[j] != '\0')
				j++;
			if ((array[k] = ft_strsplit_fuck_norminette(str, i, j, c)))
				k++;
			i = j - 1;
		}
		i++;
	}
	array[k] = NULL;
	return (!str ? NULL : array);
}
