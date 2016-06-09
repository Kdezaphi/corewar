/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 16:42:17 by mgiraud-          #+#    #+#             */
/*   Updated: 2015/03/10 14:13:20 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_get_player_color(t_vm *vm, int i, int *color)
{
	unsigned int	j;
	char			mod;

	j = -1;
	ft_memset(color, 0, sizeof(int) * 3);
	mod = 0;
	while (++j < vm->nb_player)
	{
		if (vm->info_player[j].num_player == vm->arena_player[i])
		{
			if (vm->info_player[j].color == RED)
				color[0] = (mod & 1) == 0 ? 255 : 150;
			else if (vm->info_player[j].color == GREEN)
				color[1] = (mod & (1 << 1)) == 0 ? 255 : 150;
			else if (vm->info_player[j].color == BLUE)
				color[2] = (mod & (1 << 2)) == 0 ? 255 : 150;
			else if (vm->info_player[j].color == MAGENTA && (color[0] = 255))
				color[1] = (mod & (1 << 3)) == 0 ? 255 : 150;
			else if (vm->info_player[j].color == YELLOW && (color[0] = 255))
				color[2] = (mod & (1 << 4)) == 0 ? 255 : 150;
			else if (vm->info_player[j].color == CYAN && (color[2] = 255))
				color[1] = (mod & (1 << 5)) == 0 ? 255 : 150;
		}
	}
	return ;
}

void	ft_get_player_color_by_player(t_vm *vm, int i, int *color)
{
	unsigned int col;

	col = vm->info_player[i].color;
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	if (col == RED)
		color[0] = 255;
	else if (col == GREEN)
		color[1] = 255;
	else if (col == BLUE)
		color[2] = 255;
	else if (col == MAGENTA && (color[0] = 255))
		color[1] = 255;
	else if (col == YELLOW && (color[0] = 255))
		color[2] = 255;
	else if (col == CYAN && (color[2] = 255))
		color[1] = 255;
	return ;
}

void	ft_fill_sdl_color(SDL_Color *color, int r, int g, int b)
{
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = 255;
}
