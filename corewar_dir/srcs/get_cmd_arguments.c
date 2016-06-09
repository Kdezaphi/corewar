/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_arguments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 10:17:34 by mgiraud-          #+#    #+#             */
/*   Updated: 2015/03/07 11:57:39 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char		ft_check_register(char c)
{
	if (c < 1 || c > 16)
		return (0);
	return (c);
}

char		*ft_get_encoding_code(char c)
{
	char	*str;
	int		i;
	int		k;

	str = (char*)malloc(sizeof(char) * 4);
	ft_bzero(str, 4);
	i = 7;
	k = 0;
	while (i > 0)
	{
		if (c & (1 << i))
		{
			if (c & (1 << (i - 1)))
				str[k] = 'i';
			else
				str[k] = 'd';
		}
		else if (c & (1 << (i - 1)))
			str[k] = 'r';
		i -= 2;
		k++;
	}
	return (str);
}
