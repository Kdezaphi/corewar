/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamano <atamano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 14:02:21 by atamano           #+#    #+#             */
/*   Updated: 2015/02/19 14:02:22 by atamano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

char	*ft_reverse_chr(char *s, int c)
{
	int		i;
	char	ch;

	ch = c;
	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (const char)ch)
		{
			s[i] = '\0';
			return (s);
		}
		i--;
	}
	return (NULL);
}

void	ft_write_program(int fd, t_asm *st_asm)
{
	t_list	*list;

	list = st_asm->list;
	while (list)
	{
		if (ft_write_opcode(fd, ((t_line *)list->content)->opcode) < 0)
		{
			list = list->next;
			continue ;
		}
		ft_write_encoding(fd, ((t_line *)list->content)->args,
			((t_line *)list->content)->opcode);
		ft_write_arguments(fd, list, st_asm->label);
		list = list->next;
	}
}

void	ft_convert_file(t_asm *st_asm)
{
	int	fd;

	fd = ft_create_cor(st_asm);
	if (fd < 0)
		ft_error("Error in creating file", 0, ASM_EXIT);
	ft_write_header(fd, st_asm);
	ft_write_program(fd, st_asm);
	close(fd);
}

void	ft_write_blank(int len, int fd)
{
	int i;

	i = -1;
	while (++i < len)
		ft_printf_fd(fd, "%c", 0);
}
