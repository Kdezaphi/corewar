/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/21 10:08:29 by mgiraud-          #+#    #+#             */
/*   Updated: 2015/03/10 10:13:34 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_graphical_mode2(t_vm *vm, SDL_Rect *byte, int i)
{
	if (SDL_RenderDrawRect(vm->sdl.renderer, byte) < -1)
	{
		ft_printf_fd(2, "Can not create rectangle, (%s)", SDL_GetError());
		exit(0);
	}
	if (SDL_RenderFillRect(vm->sdl.renderer, byte) < 0)
	{
		ft_printf_fd(2, "Could not fill rectangle, (%s)", SDL_GetError());
		exit(0);
	}
	if (vm->sdl.dump_byte)
		ft_dump_byte(vm, i, byte);
}

void		ft_graphical_mode(t_vm *vm, double to_wait)
{
	int			i;
	int			color[3];
	SDL_Rect	byte;

	if (to_wait > 0)
		usleep(to_wait);
	SDL_SetRenderDrawColor(vm->sdl.renderer, 0, 0, 0, 255);
	SDL_RenderClear(vm->sdl.renderer);
	SDL_SetRenderDrawColor(vm->sdl.renderer, 255, 255, 255, 255);
	ft_print_players(vm);
	ft_print_datas(vm);
	i = -1;
	while (++i < MEM_SIZE)
	{
		byte.x = i % (int)sqrt(MEM_SIZE) * RECTANGLE_SIZE;
		byte.y = i / (int)sqrt(MEM_SIZE) * RECTANGLE_SIZE + WINDOW_Y_OFFSET;
		byte.w = RECTANGLE_SIZE;
		byte.h = RECTANGLE_SIZE;
		ft_get_player_color(vm, i, color);
		SDL_SetRenderDrawColor(vm->sdl.renderer, color[0], color[1],
			color[2], 255);
		ft_graphical_mode2(vm, &byte, i);
	}
	ft_print_pc(vm);
	SDL_RenderPresent(vm->sdl.renderer);
}

static void	ft_initiate_window2(t_vm *vm, int *size)
{
	vm->sdl.font2 = TTF_OpenFont("courier-new.ttf", OPTION_FONT_SIZE);
	if (!vm->sdl.font)
	{
		ft_printf("TTF_OpenFont: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	vm->sdl.pwindow = SDL_CreateWindow("Corewar", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, *size + WINDOW_X_OFFSET,
		*size + WINDOW_Y_OFFSET, SDL_WINDOW_SHOWN);
	if (!vm->sdl.pwindow)
		my_error("Could not create SDL window", 0);
	vm->sdl.renderer = SDL_CreateRenderer(vm->sdl.pwindow,
		-1, SDL_RENDERER_ACCELERATED);
	if (!vm->sdl.renderer)
	{
		ft_printf_fd(2, "Could not create renderer (%s)\n", SDL_GetError());
		exit(0);
	}
	SDL_SetRenderDrawColor(vm->sdl.renderer, 0, 0, 0, 255);
	SDL_RenderClear(vm->sdl.renderer);
}

void		ft_initiate_window(t_vm *vm)
{
	int	size;

	size = sqrt(MEM_SIZE) * RECTANGLE_SIZE;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		ft_printf_fd(2, "Could not load SDL (%s)\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if (TTF_Init() == -1)
	{
		ft_printf("TTF_Init: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	vm->sdl.font = TTF_OpenFont("clonewars2.ttf", PLAYER_FONT_SIZE);
	if (!vm->sdl.font)
	{
		ft_printf("TTF_OpenFont: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	ft_initiate_window2(vm, &size);
}

void		ft_destroy_window(t_vm *vm)
{
	TTF_CloseFont(vm->sdl.font);
	TTF_CloseFont(vm->sdl.font2);
	SDL_DestroyRenderer(vm->sdl.renderer);
	SDL_DestroyWindow(vm->sdl.pwindow);
	TTF_Quit();
	SDL_Quit();
}
