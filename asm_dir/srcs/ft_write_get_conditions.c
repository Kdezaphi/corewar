/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conditions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamano <atamano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 16:21:01 by atamano           #+#    #+#             */
/*   Updated: 2015/02/19 16:21:02 by atamano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

int		ft_write_opcode2(int fd, char *str)
{
	if (!ft_strcmp(str, "ldi"))
		ft_putchar_fd(0x0a, fd);
	else if (!ft_strcmp(str, "sti"))
		ft_putchar_fd(0x0b, fd);
	else if (!ft_strcmp(str, "fork"))
		ft_putchar_fd(0x0c, fd);
	else if (!ft_strcmp(str, "lld"))
		ft_putchar_fd(0x0d, fd);
	else if (!ft_strcmp(str, "lldi"))
		ft_putchar_fd(0x0e, fd);
	else if (!ft_strcmp(str, "lfork"))
		ft_putchar_fd(0x0f, fd);
	else if (!ft_strcmp(str, "aff"))
		ft_putchar_fd(0x10, fd);
	else
		return (-1);
	return (0);
}

int		ft_write_opcode(int fd, char *str)
{
	if (!ft_strcmp(str, "live"))
		ft_putchar_fd(0x01, fd);
	else if (!ft_strcmp(str, "ld"))
		ft_putchar_fd(0x02, fd);
	else if (!ft_strcmp(str, "st"))
		ft_putchar_fd(0x03, fd);
	else if (!ft_strcmp(str, "add"))
		ft_putchar_fd(0x04, fd);
	else if (!ft_strcmp(str, "sub"))
		ft_putchar_fd(0x05, fd);
	else if (!ft_strcmp(str, "and"))
		ft_putchar_fd(0x06, fd);
	else if (!ft_strcmp(str, "or"))
		ft_putchar_fd(0x07, fd);
	else if (!ft_strcmp(str, "xor"))
		ft_putchar_fd(0x08, fd);
	else if (!ft_strcmp(str, "zjmp"))
		ft_putchar_fd(0x09, fd);
	else
		return (ft_write_opcode2(fd, str));
	return (0);
}

int		ft_has_encoding(char *opcode)
{
	if (!ft_strcmp(opcode, "live"))
		return (0);
	else if (!ft_strcmp(opcode, "zjmp"))
		return (0);
	else if (!ft_strcmp(opcode, "fork"))
		return (0);
	else if (!ft_strcmp(opcode, "lfork"))
		return (0);
	return (1);
}

int		ft_get_label_size(char *str)
{
	if (!ft_strcmp(str, "live") || !ft_strcmp(str, "ld")
		|| !ft_strcmp(str, "and") || !ft_strcmp(str, "or")
		|| !ft_strcmp(str, "xor") || !ft_strcmp(str, "lld"))
		return (4);
	else if (!ft_strcmp(str, "st") || !ft_strcmp(str, "add")
		|| !ft_strcmp(str, "sub") || !ft_strcmp(str, "aff"))
		ft_error("command with bad argument", 0, ASM_EXIT);
	return (2);
}
