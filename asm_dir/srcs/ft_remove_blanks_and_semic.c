/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_blanks_and_semic.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rankierm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 20:04:45 by rankierm          #+#    #+#             */
/*   Updated: 2015/02/23 18:45:38 by rankierm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

char	*ft_remove_blanks_and_semic(char *s)
{
	int		index_semic;
	char	*tmp;
	char	*ret;

	if (!s)
		return (NULL);
	if (!(*s) || *s == COMMENT_CHAR)
		return (NULL);
	index_semic = ft_strchri(s, ';');
	if (index_semic > 0)
	{
		tmp = ft_strsub(s, 0, index_semic);
		ret = ft_strtrim(tmp);
		free(tmp);
	}
	else
		ret = ft_strtrim(s);
	return (ret);
}
