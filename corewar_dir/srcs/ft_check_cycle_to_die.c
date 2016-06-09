/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cycle_to_die.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/22 12:08:42 by mgiraud-          #+#    #+#             */
/*   Updated: 2015/03/10 13:43:18 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_update_vm(t_vm *vm)
{
	unsigned int	i;

	i = 0;
	vm->cycle_to_die -= CYCLE_DELTA;
	vm->last_cycle_dec = vm->cur_cycle;
	vm->check = 0;
	while (i < vm->nb_player)
	{
		if (vm->info_player[i].nb_live >= 0 && vm->cycle_to_die > 0)
			vm->info_player[i].nb_live = 0;
		i++;
	}
	if (vm->verbose)
		ft_printf("Cycle to die is now %d\n", vm->cycle_to_die);
}

static int	ft_kill_proc(t_vm *vm, t_list **cur, t_list **prev,
	t_player **cur_player)
{
	t_list		*temp;

	if ((*prev) != NULL)
	{
		(*prev)->next = (*cur)->next;
		if (vm->verbose)
			ft_printf("The processus %d owned by %s was killed\n",
				(*cur_player)->num_proc, (*cur_player)->prog_name);
		temp = (*cur);
		(*cur) = temp->next;
		free(temp);
		return (1);
	}
	else
	{
		vm->player = (*cur)->next;
		if (vm->verbose)
			ft_printf("The processus %d owned by %s was killed\n",
				(*cur_player)->num_proc, (*cur_player)->prog_name);
		free(*cur);
		*cur = vm->player;
		return (1);
	}
	return (0);
}

static void	ft_check_living_processus(t_vm *vm)
{
	t_list		*cur;
	t_list		*prev;
	t_player	*cur_player;

	cur = vm->player;
	prev = NULL;
	while (cur != NULL)
	{
		cur_player = (t_player *)cur->content;
		if (cur_player->live == 0)
		{
			if (ft_kill_proc(vm, &cur, &prev, &cur_player))
				continue ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void		ft_check_to_die(t_vm *vm)
{
	unsigned int sum;
	unsigned int i;

	sum = 0;
	i = -1;
	if (vm->cycle_to_die > 0 && (vm->cur_cycle - vm->last_cycle_dec)
		% vm->cycle_to_die == 0)
	{
		ft_check_living_processus(vm);
		while (++i < vm->nb_player)
		{
			if (vm->info_player[i].nb_live <= 0)
				vm->info_player[i].nb_live = -1;
			else if (vm->info_player[i].nb_live != -1)
				sum += vm->info_player[i].nb_live;
		}
		if (sum >= NBR_LIVE)
			ft_update_vm(vm);
		else
			vm->check++;
		ft_update_live_player(vm);
	}
	if (vm->check >= MAX_CHECKS)
		ft_update_vm(vm);
}
