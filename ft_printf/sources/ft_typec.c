/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_typec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 12:12:21 by kdezaphi          #+#    #+#             */
/*   Updated: 2014/12/10 12:12:22 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_paddingchar(t_flags *flags)
{
	char	*pad;
	int		i;

	i = -1;
	pad = (char*)malloc(flags->size);
	if (flags->zero && !flags->neg)
		while (++i < flags->size - 1)
			pad[i] = '0';
	else
		while (++i < flags->size - 1)
			pad[i] = ' ';
	pad[i] = '\0';
	return (pad);
}

int		ft_padczero(t_flags *flags)
{
	char	*pad;
	int		i;

	i = -1;
	pad = (char*)malloc(flags->size - 1);
	if (flags->zero && !flags->neg)
		while (++i < flags->size - 1)
			pad[i] = '0';
	else
		while (++i < flags->size - 1)
			pad[i] = ' ';
	pad[i] = '\0';
	if (flags->neg)
	{
		ft_putchar_fd('\0', flags->fd);
		ft_putstr_fd(pad, flags->fd);
	}
	else
	{
		ft_putstr_fd(pad, flags->fd);
		ft_putchar_fd('\0', flags->fd);
	}
	free(pad);
	return (flags->size);
}

int		ft_affichec(char c, t_flags *flags)
{
	char	*pad;

	if (c == 0 && flags->size)
		return (ft_padczero(flags));
	if (flags->size > 1)
	{
		pad = ft_paddingchar(flags);
		if (!flags->neg)
			ft_putstr_fd(pad, flags->fd);
		ft_putchar_fd(c, flags->fd);
		if (flags->neg)
			ft_putstr_fd(pad, flags->fd);
		free(pad);
		return (flags->size);
	}
	ft_putchar_fd(c, flags->fd);
	return (1);
}
