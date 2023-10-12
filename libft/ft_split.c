/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbigourd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:01:34 by hbigourd          #+#    #+#             */
/*   Updated: 2022/11/20 15:40:14 by hbigourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_issep(char const c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static size_t	ft_countwords(char const *str, char sep)
{
	size_t	countw;
	int		i;

	countw = 1;
	i = -1;
	while (str[++i])
		if (!ft_issep(str[i], sep) && ft_issep(str[i + 1], sep) && str[i + 2])
			countw ++;
	if (!ft_issep(sep, '\0'))
		countw ++;
	i = -1;
	return (countw);
}

static size_t	ft_lentosep(char const *str, size_t f, char sep)
{
	size_t	i;

	i = 0;
	while (!ft_issep(str[f + i], sep) && str[f + i])
		i ++;
	i ++;
	return (i);
}

static char	*write_splited(size_t ind, char const *str, char sep)
{
	size_t	len;
	size_t	j;
	char	*splited;

	len = ft_lentosep(str, ind, sep);
	splited = malloc(sizeof(char) * len);
	if (!splited)
		return (NULL);
	j = 0;
	while (str[ind + j] && j < len - 1)
	{
		splited[j] = str[ind + j];
		j ++;
	}
	splited[j] = '\0';
	return (splited);
}

char	**ft_split(char const *s, char sep)
{
	char	**split;
	size_t	i;
	size_t	countw;

	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * ft_countwords(s, sep));
	if (!split)
		return (NULL);
	i = 0;
	countw = 0;
	while (s[i] && countw < ft_countwords(s, sep) - 1)
	{
		if (!ft_issep(s[i], sep))
		{
			split[countw] = write_splited(i, s, sep);
			if (!split[countw])
				return (NULL);
			countw ++;
			i += ft_lentosep(s, i, sep) - 1;
		}
		i ++;
	}
	split[countw] = NULL;
	return (split);
}
