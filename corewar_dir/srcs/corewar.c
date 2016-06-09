/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 17:44:53 by mgiraud-          #+#    #+#             */
/*   Updated: 2015/03/10 13:34:52 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_get_args(int ac, char **av, t_vm *vm)
{
	int		i;
	int		cur_player;

	i = 0;
	cur_player = 0;
	ft_printf("Introducing contestants...\n");
	while (++i < ac)
	{
		if (*av[i] == '-')
		{
			if (!ft_strcmp(av[i], "-dump") && av[i + 1]
				&& ft_is_number(av[i + 1]) && i++)
				vm->dump_cycle = ft_atoi(av[i]) > 0 ? ft_atoi(av[i]) : -1;
			else if (!ft_strcmp(av[i], "-n") && av[i + 1]
				&& ft_is_number(av[i + 1]) && (i += 2))
				ft_new_player(vm, av[i], ft_atoi(av[i - 1]), &cur_player);
			else if (!ft_strcmp(av[i], "-g"))
				vm->graphical_mode = 1;
			else if (!ft_strcmp(av[i], "-v"))
				vm->verbose = 1;
		}
		else
			ft_new_player(vm, av[i], -1, &cur_player);
	}
	ft_make_arena(vm, cur_player);
}

static void	main_loop(t_vm *vm)
{
	t_player	*play;
	t_list		*cur;

	cur = vm->player;
	while (cur != NULL)
	{
		play = (t_player *)cur->content;
		if (vm->cur_cycle == 0)
			play->next_cycle_inst = vm->bytecode[vm->arena[play->pc]].nb_cycle;
		if (play->next_cycle_inst == 0)
		{
			if (vm->arena[play->pc] > 0 && vm->arena[play->pc] < 17)
				vm->bytecode[vm->arena[play->pc]].f(vm, play);
			else
				play->pc = (play->pc + 1) % MEM_SIZE;
			if (vm->arena[play->pc] > 0 && vm->arena[play->pc] < 17)
				play->next_cycle_inst =
					vm->bytecode[vm->arena[play->pc]].nb_cycle - 1;
		}
		else
			play->next_cycle_inst--;
		cur = cur->next;
	}
}

static void	ft_handle_event(t_vm *vm)
{
	if (vm->sdl.event.type == SDL_QUIT)
	{
		vm->finished = 1;
		vm->paused = 0;
	}
	if (vm->sdl.event.type == SDL_KEYDOWN)
	{
		if (vm->sdl.event.key.keysym.sym == SDLK_ESCAPE)
		{
			vm->finished = 1;
			vm->paused = 0;
		}
		else if (vm->sdl.event.key.keysym.sym == SDLK_SPACE)
			vm->paused = !vm->paused;
		else if (vm->sdl.event.key.keysym.sym == SDLK_d)
			vm->sdl.dump_byte = !vm->sdl.dump_byte;
		else if (vm->sdl.event.key.keysym.sym == SDLK_l)
			vm->display_proc_list = !vm->display_proc_list;
	}
}

static void	ft_split_main(t_vm *vm, clock_t *start, double *to_wait)
{
	if (SDL_PollEvent(&vm->sdl.event))
		ft_handle_event(vm);
	while (vm->paused)
		if (SDL_PollEvent(&vm->sdl.event))
			ft_handle_event(vm);
	*start = clock();
	if (vm->display_proc_list)
		ft_display_proc(vm);
	main_loop(vm);
	if (vm->cur_cycle > 0)
		ft_check_to_die(vm);
	*to_wait = (1.0 / (double)CYCLE_PER_SEC - (double)(clock() - *start)
		/ SEC) * SEC;
	if (vm->cycle_to_die <= 0)
		vm->finished = 1;
	else if (vm->graphical_mode)
		ft_graphical_mode(vm, *to_wait);
	vm->cur_cycle++;
	if (vm->dump_cycle > 0 && (int)vm->cur_cycle >= vm->dump_cycle)
		vm->finished = 1;
	if (vm->verbose)
		ft_printf("It is now cycle %u\n", vm->cur_cycle);
}

int			main(int ac, char **av)
{
	t_vm		vm;
	clock_t		start;
	double		to_wait;

	if (ac < 2)
		ft_usage_error();
	else
	{
		ft_initialize_vm(&vm);
		ft_get_args(ac, av, &vm);
		if (vm.graphical_mode)
			ft_initiate_window(&vm);
		while (!vm.finished)
			ft_split_main(&vm, &start, &to_wait);
		ft_print_arena(&vm);
		ft_printf("cycle: %d\n", vm.cur_cycle);
		ft_print_winner(&vm);
		if (vm.graphical_mode)
			ft_destroy_window(&vm);
	}
	return (0);
}
