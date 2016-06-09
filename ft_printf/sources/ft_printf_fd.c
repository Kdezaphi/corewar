/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 15:06:48 by kdezaphi          #+#    #+#             */
/*   Updated: 2015/01/13 15:06:50 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_backslash_fd(char c, int fd)
{
	char	*escape;

	escape = ft_strdup("abfnrtv01234567");
	if ((ft_strchr(escape, c)))
		ft_putchar_fd(ft_charescape(c), fd);
	else
		ft_putchar_fd(c, fd);
	free(escape);
}

int		ft_percent_fd(const char *str, int *res, va_list *ap, int fd)
{
	int		i;
	char	*str_flags;
	char	*str_type;
	t_flags	*flags;

	i = 0;
	str_flags = ft_strdup("#0-+*. hljz1234567890");
	str_type = ft_strdup("sSpdDioOuUxXcC");
	flags = ft_initflags();
	flags->fd = fd;
	while (!ft_strchr(str_type, str[i]) && ft_strchr(str_flags, str[i]))
	{
		if (ft_strchr(str_flags, str[i]))
			i += ft_flags(&str[i], flags, ap);
		i++;
	}
	if ((ft_strchr(str_type, str[i])) && str[i])
		ft_type(str[i], res, flags, ap);
	else if (str[i])
		*res += ft_notype(str[i], flags);
	free(str_flags);
	free(str_type);
	free(flags->mod);
	free(flags);
	return (++i);
}

int		ft_printf_fd(int fd, const char *str, ...)
{
	va_list ap;
	int		i;
	int		res;

	i = -1;
	res = 0;
	va_start(ap, str);
	while (++i < (int)ft_strlen(str))
	{
		if (str[i] == '%')
			i += ft_percent_fd(&str[i + 1], &res, &ap, fd);
		else if (str[i] == '\\')
		{
			ft_backslash_fd(str[i + 1], fd);
			res++;
		}
		else
		{
			ft_putchar_fd(str[i], fd);
			res++;
		}
	}
	va_end(ap);
	return (res);
}
