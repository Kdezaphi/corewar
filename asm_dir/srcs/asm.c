/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 17:51:05 by mgiraud-          #+#    #+#             */
/*   Updated: 2015/02/24 14:21:14 by rankierm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int ac, char **av)
{
	t_asm	st_asm;
	int		fd;

	if (ac == 2)
	{
		ft_t_asm_init(&st_asm);
		fd = ft_open_file(av[1], &st_asm);
		ft_first_gnl(fd, &st_asm);
		ft_check_last_error(st_asm);
		ft_convert_file(&st_asm);
		ft_t_asm_free(&st_asm);
	}
	else
		ft_error("Usage: ./asm file.s", 0, ASM_EXIT);
	return (0);
}
