/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamano <atamano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 16:35:34 by atamano           #+#    #+#             */
/*   Updated: 2015/03/09 16:37:28 by atamano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include <fcntl.h>

char	*ft_remove_cor(char *str)
{
	int i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] != '.')
		i--;
	str[i] = '\0';
	return (str);
}

void	ft_encode_args(char *c, char *str, int place)
{
	char b;

	b = *c;
	if (str[0] == 'r')
		b = b | (1 << (6 - (place * 2)));
	else if (str[0] == '%')
		b = b | (1 << (7 - (place * 2)));
	else
	{
		b = b | (1 << (7 - (place * 2)));
		b = b | (1 << (6 - (place * 2)));
	}
	*c = b;
}

void	ft_write_header(int fd, t_asm *st_asm)
{
	int i;
	int	len;

	i = rev_int(COREWAR_EXEC_MAGIC);
	ft_write_int(fd, i);
	st_asm->header.name = ft_remove_cor(st_asm->header.name);
	ft_putstr_fd(st_asm->header.name, fd);
	len = ft_strlen(st_asm->header.name);
	len = PROG_NAME_LENGTH - len + 4;
	if (len < 0)
		ft_error("Name too big", 0, ASM_EXIT);
	ft_write_blank(len, fd);
	i = st_asm->header.prog_size;
	i = rev_int(i);
	ft_write_int(fd, i);
	ft_printf_fd(fd, "%s", st_asm->header.comment);
	len = ft_strlen(st_asm->header.comment);
	len = COMMENT_LENGTH - len + 4;
	if (len < 0)
		ft_error("Comments too big", 0, ASM_EXIT);
	ft_write_blank(len, fd);
}

void	ft_write_encoding(int fd, char **args, char *opcode)
{
	char	c;
	int		len;

	len = ft_tablen(args);
	c = 0;
	if (ft_has_encoding(opcode))
	{
		if (len > 0)
			ft_encode_args(&c, args[0], 0);
		if (len > 1)
			ft_encode_args(&c, args[1], 1);
		if (len > 2)
			ft_encode_args(&c, args[2], 2);
		ft_printf_fd(fd, "%c", c);
	}
}

int		ft_create_cor(t_asm *st_asm)
{
	char	*str;
	int		fd;

	str = ft_reverse_chr(st_asm->file_name, '.');
	if (str)
		str = ft_strjoin(str, ".cor");
	else
		str = ft_strjoin(st_asm->file_name, ".cor");
	fd = open(str, O_CREAT | O_TRUNC | O_RDWR, 0666);
	free(str);
	return (fd);
}
