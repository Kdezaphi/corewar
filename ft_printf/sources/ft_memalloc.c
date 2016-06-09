/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 09:53:19 by kdezaphi          #+#    #+#             */
/*   Updated: 2014/11/05 11:52:52 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*mem;
	char	*tmp;
	size_t	i;

	if (size == 0)
		mem = NULL;
	else
	{
		mem = malloc(size);
		if (mem)
		{
			tmp = (char *)mem;
			i = -1;
			while (++i < size)
				tmp[i] = '\0';
		}
	}
	return (mem);
}
