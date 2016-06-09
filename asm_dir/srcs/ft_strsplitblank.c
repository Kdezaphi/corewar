/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitblank.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <kdezaphi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 12:34:54 by rankierm          #+#    #+#             */
/*   Updated: 2016/02/18 17:07:23 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_nbwordblank(const char *s)
{
	size_t	i;
	size_t	flag;

	if (!s)
		return (0);
	i = 0;
	flag = 1;
	while (*s)
	{
		if (!ft_isblank(*s) && flag)
		{
			i++;
			flag = 0;
		}
		if (ft_isblank(*s) && !flag)
			flag = 1;
		s++;
	}
	return (i);
}

static void	ft_feedtab(char **tab, const char *s)
{
	size_t	flag;
	size_t	i;
	size_t	start;

	start = 0;
	flag = 1;
	i = 0;
	while (s[i])
	{
		if (!ft_isblank(s[i]) && flag)
		{
			start = i;
			flag = 0;
		}
		if (ft_isblank(s[i]) && !flag)
		{
			*tab = ft_strsub(s, start, i - start);
			tab++;
			flag = 1;
		}
		i++;
	}
	if (!flag)
		*tab = ft_strsub(s, start, i - start);
}

char		**ft_strsplitblank(char const *s)
{
	size_t	nbword;
	char	**tab;

	if (!s)
		return (NULL);
	nbword = ft_nbwordblank(s) + 1;
	if (nbword == 1)
		return (NULL);
	tab = (char **)ft_memalloc(sizeof(char *) * nbword);
	if (tab)
	{
		ft_feedtab(tab, s);
		tab[nbword - 1] = NULL;
	}
	return (tab);
}
