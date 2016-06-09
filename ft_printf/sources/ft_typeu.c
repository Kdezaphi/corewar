/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_typeu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 12:17:01 by kdezaphi          #+#    #+#             */
/*   Updated: 2014/12/10 12:17:03 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		ft_paduzero(t_flags *flags)
{
	int		i;

	i = -1;
	if (flags->neg)
	{
		ft_putchar_fd('0', flags->fd);
		if (flags->size == 0)
			return (1);
	}
	while (++i < flags->size)
		ft_putchar_fd(' ', flags->fd);
	return (flags->size);
}

int		ft_afficheu(unsigned long long nb, t_flags *flags)
{
	char	*tmp;
	int		res;

	tmp = ft_llbtoa(nb, "0123456789");
	if (flags->pre > (int)ft_strlen(tmp))
		tmp = ft_prenum(tmp, flags->pre - ft_strlen(tmp));
	if (flags->pre == 0 && nb == 0)
	{
		free(tmp);
		if (flags->size > 0)
			return (ft_paduzero(flags));
		return (0);
	}
	if (flags->size > (int)ft_strlen(tmp))
	{
		flags->space = 0;
		flags->pos = 0;
		tmp = ft_paddpos(tmp, flags);
	}
	ft_putstr_fd(tmp, flags->fd);
	res = ft_strlen(tmp);
	free(tmp);
	return (res);
}
