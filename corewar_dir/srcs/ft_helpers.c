/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 16:32:43 by mgiraud-          #+#    #+#             */
/*   Updated: 2015/03/07 10:44:34 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_is_number(char *str)
{
	while (*str != 0)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

void	ft_memrev(void *ptr, size_t n)
{
	size_t	i;
	char	*str;
	char	tmp;

	str = (char*)ptr;
	i = 0;
	while (i < (n + 1) / 2)
	{
		tmp = str[i];
		str[i] = str[n - i - 1];
		str[n - i - 1] = tmp;
		i++;
	}
}
