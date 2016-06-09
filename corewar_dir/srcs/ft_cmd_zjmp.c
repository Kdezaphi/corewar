/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_zjmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/22 23:38:48 by kdezaphi          #+#    #+#             */
/*   Updated: 2015/03/09 16:24:42 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_cmd_zjmp_verbose(t_vm *vm, t_player *player, int jump, int param)
{
	int		i;

	ft_printf("P %4d | zjmp %d FAILED\n", player->num_proc, param);
	ft_printf("ADV %d (%#06x -> %#06x) ", jump, player->pc,
		(player->pc + jump) % MEM_SIZE);
	i = -1;
	while (++i < 3)
		ft_printf("%02x ", vm->arena[(player->pc + i) % MEM_SIZE]);
	ft_printf("\n");
}

void	ft_cmd_zjmp(t_vm *vm, t_player *player)
{
	int		param;
	int		jump;

	jump = 3;
	param = ft_param(vm, player, 1, 2);
	if (!player->carry)
	{
		player->pc = (player->pc + param % IDX_MOD) % MEM_SIZE;
		if (vm->verbose)
			ft_printf("P %4d | zjmp %d OK\n", player->num_proc, param);
	}
	else
	{
		if (vm->verbose)
			ft_cmd_zjmp_verbose(vm, player, jump, param);
		player->pc = (player->pc + jump) % MEM_SIZE;
	}
}
