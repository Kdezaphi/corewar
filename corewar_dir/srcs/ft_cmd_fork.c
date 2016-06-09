/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 17:47:54 by mgiraud-          #+#    #+#             */
/*   Updated: 2015/03/02 14:20:39 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_fork_verbose(t_player *player, int *jump, t_vm *vm)
{
	int i;

	if (vm->verbose)
	{
		ft_printf("ADV %d (%#06x -> %#06x) ", *jump, player->pc,
			(player->pc + *jump) % MEM_SIZE);
		i = -1;
		while (++i < *jump)
			ft_printf("%02x ", vm->arena[(player->pc + i) % MEM_SIZE]);
		ft_printf("\n");
	}
}

void		ft_cmd_fork(t_vm *vm, t_player *player)
{
	t_player	*child;
	t_list		*new_proc;
	int			param;
	int			jump;

	jump = 3;
	param = ft_param(vm, player, 1, 2);
	if (!(child = (t_player*)malloc(sizeof(t_player))))
		my_error("corewar", errno);
	vm->nb_proc++;
	ft_memcpy(child, player, sizeof(t_player));
	child->num_proc = vm->nb_proc;
	child->pc = (unsigned int)(child->pc + param % IDX_MOD) % MEM_SIZE;
	if (vm->arena[child->pc] > 0 && vm->arena[child->pc] < 17)
		child->next_cycle_inst =
			vm->bytecode[vm->arena[child->pc]].nb_cycle - 1;
	if (!(new_proc = ft_lstnew(child, sizeof(t_player))))
		my_error("corewar", errno);
	free(child);
	ft_lstadd(&vm->player, new_proc);
	if (vm->verbose)
		ft_printf("P %4d | fork %d (%d)\n", player->num_proc, param, child->pc);
	ft_fork_verbose(player, &jump, vm);
	player->pc = (player->pc + jump) % MEM_SIZE;
}

static void	ft_lfork_verbose(t_player *player, int *jump, t_vm *vm)
{
	int i;

	if (vm->verbose)
	{
		ft_printf("ADV %d (%#06x -> %#06x) ", *jump, player->pc,
			(player->pc + *jump) % MEM_SIZE);
		i = -1;
		while (++i < *jump)
			ft_printf("%02x ", vm->arena[(player->pc + i) % MEM_SIZE]);
		ft_printf("\n");
	}
}

void		ft_cmd_lfork(t_vm *vm, t_player *player)
{
	t_player	*child;
	t_list		*new_proc;
	int			param;
	int			jump;

	jump = 3;
	param = ft_param(vm, player, 1, 2);
	if (!(child = (t_player*)malloc(sizeof(t_player))))
		my_error("corewar", errno);
	vm->nb_proc++;
	ft_memcpy(child, player, sizeof(t_player));
	child->num_proc = vm->nb_proc;
	child->pc = (unsigned int)(child->pc + param) % MEM_SIZE;
	if (vm->arena[child->pc] > 0 && vm->arena[child->pc] < 17)
		child->next_cycle_inst =
			vm->bytecode[vm->arena[child->pc]].nb_cycle - 1;
	if (!(new_proc = ft_lstnew(child, sizeof(t_player))))
		my_error("corewar", errno);
	free(child);
	ft_lstadd(&vm->player, new_proc);
	if (vm->verbose)
		ft_printf("P %4d | lfork %d (%d)\n", player->num_proc,
			param, child->pc);
	ft_lfork_verbose(player, &jump, vm);
	player->pc = (player->pc + jump) % MEM_SIZE;
}
