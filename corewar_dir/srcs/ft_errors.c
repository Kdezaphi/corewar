/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 18:27:47 by mgiraud-          #+#    #+#             */
/*   Updated: 2015/02/22 09:17:10 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_usage_error(void)
{
	ft_printf_fd(2, "Here is a fuckin long message\n");
	exit(EXIT_FAILURE);
}

void	my_error(char *str, int is_perror)
{
	if (is_perror)
	{
		perror(strerror(errno));
		errno = 0;
	}
	else
		ft_printf_fd(2, str);
	exit(EXIT_FAILURE);
}

void	ft_corr_encoding(char *coding, int *jump, int arg, int label_size)
{
	int		i;

	i = -1;
	while (++i < arg)
	{
		if (coding[i] == 'r')
			*jump += 1;
		else if (coding[i] == 'i')
			*jump += 2;
		else if (coding[i] == 'd')
			*jump += label_size;
	}
}
