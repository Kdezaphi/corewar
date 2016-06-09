/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_gnl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rankierm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 11:11:57 by rankierm          #+#    #+#             */
/*   Updated: 2015/02/24 14:33:24 by rankierm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

static void	ft_init_gnl(int *pos, int *nb, char **line)
{
	*pos = 0;
	*nb = 1;
	*line = NULL;
}

int			ft_first_gnl(int fd, t_asm *st_asm)
{
	char		*line;
	char		**split_l;
	int			position;
	int			line_position;

	ft_init_gnl(&position, &line_position, &line);
	while (get_next_line(fd, &line) > 0)
	{
		if ((split_l = ft_split_first_word(line)))
		{
			if (split_l[0][0] == '.')
				ft_check_header(split_l, st_asm, line_position);
			else
				ft_check_instruction(split_l, st_asm, &position, line_position);
			if (*split_l)
				ft_free_2dtable(split_l);
		}
		line_position++;
		ft_strdel(&line);
	}
	(line) ? ft_strdel(&line) : NULL;
	if (!((t_list *)st_asm->list))
		ft_error("asm error : no program instruction", 0, ASM_EXIT);
	st_asm->header.prog_size = position;
	return (0);
}
