/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_binfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 10:16:24 by kdezaphi          #+#    #+#             */
/*   Updated: 2015/02/18 10:16:26 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static unsigned int	ft_take_int(int fd)
{
	unsigned char	*str;
	unsigned int	nb;

	str = (unsigned char*)malloc(4);
	read(fd, str, 4);
	ft_memrev(str, 4);
	ft_memcpy(&nb, str, 4);
	free(str);
	return (nb);
}

static void			ft_verif_binfile_suite(int fd, char *path, t_player *player)
{
	unsigned int	nb_read;

	read(fd, player->prog_name, PROG_NAME_LENGTH + 4);
	player->prog_size = ft_take_int(fd);
	read(fd, player->comment, COMMENT_LENGTH + 4);
	if (player->prog_size != (nb_read = read(fd, player->prog, CHAMP_MAX_SIZE))
		|| player->prog_size > CHAMP_MAX_SIZE)
	{
		ft_printf_fd(2, "Error: File %s has a code size that differ from \
			what its header says\n", path);
		exit(EXIT_FAILURE);
	}
	player->prog[nb_read] = '\0';
}

void				ft_verif_binfile(char *path, t_player *player)
{
	int				fd;
	unsigned int	magic;

	if ((fd = open(path, O_RDONLY)) < 3)
	{
		ft_printf_fd(2, "Can't read source file %s\n", path);
		exit(EXIT_FAILURE);
	}
	magic = ft_take_int(fd);
	if (magic != COREWAR_EXEC_MAGIC)
	{
		ft_printf_fd(2, "Error: File %s has an invalid header\n", path);
		exit(EXIT_FAILURE);
	}
	ft_verif_binfile_suite(fd, path, player);
	close(fd);
}
