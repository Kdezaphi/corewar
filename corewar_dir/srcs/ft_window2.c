/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 16:38:05 by mgiraud-          #+#    #+#             */
/*   Updated: 2015/03/11 16:52:30 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_print_player_sum(t_vm *vm, int i)
{
	char			sumup[PROG_NAME_LENGTH + 50];
	t_texture		tex;
	t_info_player	player;
	char			*str;

	player = vm->info_player[i];
	ft_bzero(sumup, PROG_NAME_LENGTH + 50);
	ft_strcpy(sumup, "Player ");
	str = ft_itoa(player.num_player);
	ft_strcpy(&(sumup[ft_strlen(sumup)]), str);
	ft_strdel(&str);
	ft_strcpy(&(sumup[ft_strlen(sumup)]), " : ");
	ft_strcpy(&(sumup[ft_strlen(sumup)]), player.name);
	ft_fill_sdl_color(&tex.color, 255, 255, 255);
	tex.surface = TTF_RenderText_Solid(vm->sdl.font2, sumup, tex.color);
	tex.texture = SDL_CreateTextureFromSurface(vm->sdl.renderer, tex.surface);
	SDL_QueryTexture(tex.texture, NULL, NULL, &tex.tex_w, &tex.tex_h);
	tex.rect.x = vm->sdl.arena_size + 10;
	tex.rect.y = BLOCK_PLAYER_MARGIN_Y + i * 60;
	tex.rect.w = tex.tex_w;
	tex.rect.h = tex.tex_h;
	SDL_RenderCopy(vm->sdl.renderer, tex.texture, NULL, &tex.rect);
	SDL_DestroyTexture(tex.texture);
	SDL_FreeSurface(tex.surface);
}

void	ft_print_player_last_live(t_vm *vm, int i)
{
	char			live[100];
	t_texture		tex;
	t_info_player	player;
	char			*str;

	player = vm->info_player[i];
	ft_bzero(live, 100);
	ft_strcpy(live, "Last live : ");
	str = ft_itoa(player.last_live);
	ft_strcpy(&(live[ft_strlen(live)]), str);
	ft_strdel(&str);
	ft_fill_sdl_color(&tex.color, 255, 255, 255);
	tex.surface = TTF_RenderText_Solid(vm->sdl.font2, live, tex.color);
	tex.texture = SDL_CreateTextureFromSurface(vm->sdl.renderer, tex.surface);
	SDL_QueryTexture(tex.texture, NULL, NULL, &tex.tex_w, &tex.tex_h);
	tex.rect.x = vm->sdl.arena_size + 20;
	tex.rect.y = BLOCK_PLAYER_MARGIN_Y + 20 + i * 60;
	tex.rect.w = tex.tex_w;
	tex.rect.h = tex.tex_h;
	SDL_RenderCopy(vm->sdl.renderer, tex.texture, NULL, &tex.rect);
	SDL_DestroyTexture(tex.texture);
	SDL_FreeSurface(tex.surface);
}

void	ft_print_player_cur_live(t_vm *vm, int i)
{
	char			live[100];
	t_texture		tex;
	t_info_player	player;
	char			*str;

	player = vm->info_player[i];
	ft_bzero(live, 100);
	ft_strcpy(live, "Current live : ");
	str = ft_itoa(player.nb_live);
	ft_strcpy(&(live[ft_strlen(live)]), str);
	ft_strdel(&str);
	ft_fill_sdl_color(&tex.color, 255, 255, 255);
	tex.surface = TTF_RenderText_Solid(vm->sdl.font2, live, tex.color);
	tex.texture = SDL_CreateTextureFromSurface(vm->sdl.renderer, tex.surface);
	SDL_QueryTexture(tex.texture, NULL, NULL, &tex.tex_w, &tex.tex_h);
	tex.rect.x = vm->sdl.arena_size + 20;
	tex.rect.y = BLOCK_PLAYER_MARGIN_Y + 40 + i * 60;
	tex.rect.w = tex.tex_w;
	tex.rect.h = tex.tex_h;
	SDL_RenderCopy(vm->sdl.renderer, tex.texture, NULL, &tex.rect);
	SDL_DestroyTexture(tex.texture);
	SDL_FreeSurface(tex.surface);
}

void	ft_print_player_cycle_to_die(t_vm *vm)
{
	char			live[100];
	t_texture		tex;
	char			*str;

	ft_bzero(live, 100);
	ft_strcpy(live, "Cycle to die : ");
	str = ft_itoa(vm->cycle_to_die);
	ft_strcpy(&(live[ft_strlen(live)]), str);
	ft_strdel(&str);
	ft_fill_sdl_color(&tex.color, 255, 255, 255);
	tex.surface = TTF_RenderText_Solid(vm->sdl.font2, live, tex.color);
	tex.texture = SDL_CreateTextureFromSurface(vm->sdl.renderer, tex.surface);
	SDL_QueryTexture(tex.texture, NULL, NULL, &tex.tex_w, &tex.tex_h);
	tex.rect.x = vm->sdl.arena_size + 20;
	tex.rect.y = vm->sdl.arena_size / 2;
	tex.rect.w = tex.tex_w;
	tex.rect.h = tex.tex_h;
	SDL_RenderCopy(vm->sdl.renderer, tex.texture, NULL, &tex.rect);
	SDL_DestroyTexture(tex.texture);
	SDL_FreeSurface(tex.surface);
}

void	ft_print_player_cycle_delta(t_vm *vm)
{
	char			live[100];
	t_texture		tex;
	char			*cycle;

	ft_bzero(live, 100);
	ft_strcpy(live, "Cycle delta : ");
	cycle = ft_itoa(CYCLE_DELTA);
	ft_strcpy(&(live[ft_strlen(live)]), cycle);
	ft_strdel(&cycle);
	ft_fill_sdl_color(&tex.color, 255, 255, 255);
	tex.surface = TTF_RenderText_Solid(vm->sdl.font2, live, tex.color);
	tex.texture = SDL_CreateTextureFromSurface(vm->sdl.renderer, tex.surface);
	SDL_QueryTexture(tex.texture, NULL, NULL, &tex.tex_w, &tex.tex_h);
	tex.rect.x = vm->sdl.arena_size + 20;
	tex.rect.y = vm->sdl.arena_size / 2 + 20;
	tex.rect.w = tex.tex_w;
	tex.rect.h = tex.tex_h;
	SDL_RenderCopy(vm->sdl.renderer, tex.texture, NULL, &tex.rect);
	SDL_DestroyTexture(tex.texture);
	SDL_FreeSurface(tex.surface);
}
