/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 16:42:21 by mgiraud-          #+#    #+#             */
/*   Updated: 2015/03/07 10:38:35 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_print_players_data(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < (int)vm->nb_player)
	{
		ft_print_player_sum(vm, i);
		ft_print_player_last_live(vm, i);
		ft_print_player_cur_live(vm, i);
		i++;
	}
}

void	ft_print_datas(t_vm *vm)
{
	(void)vm;
	ft_print_cycle_limit(vm);
	ft_print_cur_cycle(vm);
	ft_print_players_data(vm);
	ft_print_player_cycle_to_die(vm);
	ft_print_player_cycle_delta(vm);
}

void	ft_print_players(t_vm *vm)
{
	int			color[3];
	int			i;
	t_texture	tex;

	i = -1;
	while (++i < (int)vm->nb_player)
	{
		ft_get_player_color_by_player(vm, i, color);
		tex.color.r = color[0];
		tex.color.g = color[1];
		tex.color.b = color[2];
		tex.color.a = 255;
		tex.surface = TTF_RenderText_Solid(vm->sdl.font,
			vm->info_player[i].name, tex.color);
		tex.texture = SDL_CreateTextureFromSurface(vm->sdl.renderer,
			tex.surface);
		SDL_QueryTexture(tex.texture, NULL, NULL, &tex.tex_w, &tex.tex_h);
		tex.rect.x = vm->sdl.arena_size / vm->nb_player * i;
		tex.rect.y = 0;
		tex.rect.w = tex.tex_w;
		tex.rect.h = tex.tex_h;
		SDL_RenderCopy(vm->sdl.renderer, tex.texture, NULL, &tex.rect);
		SDL_DestroyTexture(tex.texture);
		SDL_FreeSurface(tex.surface);
	}
}

void	ft_dump_byte(t_vm *vm, int i, SDL_Rect *byte)
{
	t_texture tex;

	ft_fill_sdl_color(&tex.color, 255, 255, 255);
	SDL_SetRenderDrawColor(vm->sdl.renderer, 0, 0, 0, 255);
	tex.surface = TTF_RenderText_Solid(vm->sdl.font2, ft_llbtoa(vm->arena[i],
		"0123456789abcdef"), tex.color);
	tex.texture = SDL_CreateTextureFromSurface(vm->sdl.renderer, tex.surface);
	SDL_QueryTexture(tex.texture, NULL, NULL, &tex.tex_w, &tex.tex_h);
	tex.rect.x = byte->x + 5;
	tex.rect.y = byte->y + 5;
	tex.rect.w = tex.tex_w;
	tex.rect.h = tex.tex_h;
	SDL_RenderCopy(vm->sdl.renderer, tex.texture, NULL, &tex.rect);
	SDL_DestroyTexture(tex.texture);
	SDL_FreeSurface(tex.surface);
}
