/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_live.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/22 23:05:48 by kdezaphi          #+#    #+#             */
/*   Updated: 2015/03/10 09:38:09 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void ft_cmd_live_verbose(t_vm *vm, t_player *player, int *jump)
{
	int		i;

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

void		ft_cmd_live(t_vm *vm, t_player *player)
{
	int		param;
	int		jump;
	int		i;

	jump = 5;
	param = ft_param(vm, player, 1, 4);
	i = -1;
	if (vm->verbose)
		ft_printf("P %4d | live %d\n", player->num_proc, param);
	while (++i < (int)vm->nb_player)
		if (vm->info_player[i].num_player == param)
		{
			if (vm->info_player[i].nb_live >= 0)
			{
				vm->info_player[i].nb_live++;
				player->live = 1;
				vm->info_player[i].last_live = vm->cur_cycle;
				if (vm->verbose)
					ft_printf("Player %d (%s) is said to be alive\n",
					-vm->info_player[i].num_player, vm->info_player[i].name);
			}
			break ;
		}
	ft_cmd_live_verbose(vm, player, &jump);
	player->pc = (player->pc + jump) % MEM_SIZE;
}
