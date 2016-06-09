/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 16:38:09 by mgiraud-          #+#    #+#             */
/*   Updated: 2015/03/07 10:36:23 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_print_pc2(t_vm *vm, unsigned int i)
{
	SDL_Rect	byte;
	int			color[3];

	byte.x = i % (int)sqrt(MEM_SIZE) * RECTANGLE_SIZE;
	byte.y = i / (int)sqrt(MEM_SIZE) * RECTANGLE_SIZE + WINDOW_Y_OFFSET;
	byte.w = RECTANGLE_SIZE;
	byte.h = RECTANGLE_SIZE;
	ft_get_player_color(vm, i, color);
	SDL_SetRenderDrawColor(vm->sdl.renderer, color[0] / 2,
		color[1] / 2, color[2] / 2, 255);
	if (SDL_RenderDrawRect(vm->sdl.renderer, &byte) < -1)
	{
		ft_printf_fd(2, "Can not create rectangle, (%s)", SDL_GetError());
		exit(0);
	}
	if (SDL_RenderFillRect(vm->sdl.renderer, &byte) < 0)
	{
		ft_printf_fd(2, "Could not fill rectangle, (%s)", SDL_GetError());
		exit(0);
	}
}

void		ft_print_pc(t_vm *vm)
{
	t_list		*cur;
	t_player	*player;

	cur = vm->player;
	while (cur != NULL)
	{
		player = (t_player *)cur->content;
		ft_print_pc2(vm, player->pc);
		cur = cur->next;
	}
}

void		ft_print_cycle_limit(t_vm *vm)
{
	char		*cycle_limit;
	t_texture	tex;
	char		*str;

	str = ft_itoa(CYCLE_PER_SEC);
	cycle_limit = ft_strjoin("Cycles/second limit : ", str);
	ft_strdel(&str);
	ft_fill_sdl_color(&tex.color, 255, 255, 255);
	tex.surface = TTF_RenderText_Solid(vm->sdl.font2, cycle_limit, tex.color);
	tex.texture = SDL_CreateTextureFromSurface(vm->sdl.renderer, tex.surface);
	SDL_QueryTexture(tex.texture, NULL, NULL, &tex.tex_w, &tex.tex_h);
	tex.rect.x = vm->sdl.arena_size + 10;
	tex.rect.y = 20;
	tex.rect.w = tex.tex_w;
	tex.rect.h = tex.tex_h;
	ft_strdel(&cycle_limit);
	SDL_RenderCopy(vm->sdl.renderer, tex.texture, NULL, &tex.rect);
	SDL_DestroyTexture(tex.texture);
	SDL_FreeSurface(tex.surface);
}

void		ft_print_cur_cycle(t_vm *vm)
{
	char		*cycle_limit;
	t_texture	tex;
	char		*str;

	str = ft_itoa((int)vm->cur_cycle);
	cycle_limit = ft_strjoin("Nb_cycle : ", str);
	ft_strdel(&str);
	ft_fill_sdl_color(&tex.color, 255, 255, 255);
	tex.surface = TTF_RenderText_Solid(vm->sdl.font2, cycle_limit, tex.color);
	tex.texture = SDL_CreateTextureFromSurface(vm->sdl.renderer, tex.surface);
	SDL_QueryTexture(tex.texture, NULL, NULL, &tex.tex_w, &tex.tex_h);
	tex.rect.x = vm->sdl.arena_size + 10;
	tex.rect.y = 40;
	tex.rect.w = tex.tex_w;
	tex.rect.h = tex.tex_h;
	ft_strdel(&cycle_limit);
	SDL_RenderCopy(vm->sdl.renderer, tex.texture, NULL, &tex.rect);
	SDL_DestroyTexture(tex.texture);
	SDL_FreeSurface(tex.surface);
}
