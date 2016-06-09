/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_first_word.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rankierm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/21 16:28:41 by rankierm          #+#    #+#             */
/*   Updated: 2015/02/24 13:34:11 by rankierm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*ft_get_first_word(char *s, size_t *delimiter)
{
	int		i;

	i = 0;
	while (s[i] && !ft_isblank(s[i]))
		i++;
	if (i == 0)
		return (NULL);
	*delimiter = i;
	return (ft_strsub(s, 0, i));
}

char	**ft_split_first_word(char *line)
{
	char	*tmp;
	char	*first_w;
	char	**ret;
	size_t	delimiter;

	tmp = ft_remove_blanks_and_semic(line);
	if (!tmp)
		return (NULL);
	if (!(ret = (char **)ft_memalloc(sizeof(char *) * 3)))
		ft_error("asm unexpected error: malloc -> header", 0, ASM_EXIT);
	delimiter = 0;
	if ((first_w = ft_get_first_word(tmp, &delimiter)))
	{
		ret[0] = first_w;
		ret[1] = ((tmp + delimiter)[0]) ? ft_strtrim(tmp + delimiter) : NULL;
		ret[2] = NULL;
	}
	else
		ret = NULL;
	ft_strdel(&tmp);
	return (ret);
}
