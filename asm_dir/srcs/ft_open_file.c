/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rankierm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 10:39:11 by rankierm          #+#    #+#             */
/*   Updated: 2015/02/23 13:48:09 by rankierm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

int		ft_open_file(char *file, t_asm *st_asm)
{
	int		fd;
	char	*tmp;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error(strerror(errno), 0, ASM_EXIT);
	else
	{
		tmp = ft_strrchr(file, '.');
		if (!tmp || !ft_strequ(tmp, ".s"))
			ft_error("Usage file format: [a-zA-Z0-9].s", 0, ASM_EXIT);
		else
		{
			tmp = ft_strrchr(file, '/');
			st_asm->file_name = (tmp) ? ft_strdup(tmp + 1) : ft_strdup(file);
		}
	}
	return (fd);
}
