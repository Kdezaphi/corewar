/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_binaries_util.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamano <atamano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 13:55:02 by atamano           #+#    #+#             */
/*   Updated: 2015/02/20 13:55:03 by atamano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

void	ft_write_oct(int fd, int num)
{
	int		nb;
	char	oct_a;
	char	oct_b;

	nb = num;
	nb = nb % IDX_MOD;
	oct_a = nb & 0xFF;
	oct_b = (nb >> 8) & 0xFF;
	write(fd, &oct_b, 1);
	write(fd, &oct_a, 1);
}

void	ft_write_int(int fd, int num)
{
	int		i;
	char	c[4];

	i = num;
	ft_memset(c, 0, 4);
	c[0] = i & 0xFF;
	c[1] = (i >> 8) & 0xFF;
	c[2] = (i >> 16) & 0xFF;
	c[3] = (i >> 24) & 0xFF;
	ft_putchar_fd(c[0], fd);
	ft_putchar_fd(c[1], fd);
	ft_putchar_fd(c[2], fd);
	ft_putchar_fd(c[3], fd);
}

int		rev_int(int nb)
{
	int		oct_a;
	int		oct_b;
	int		oct_c;
	int		oct_d;

	oct_a = nb & 0xFF;
	oct_b = (nb >> 8) & 0xFF;
	oct_c = (nb >> 16) & 0xFF;
	oct_d = (nb >> 24) & 0xFF;
	return (oct_a * 16777216 + oct_b * 65536 + oct_c * 256 + oct_d);
}
