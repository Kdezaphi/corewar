/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/22 22:19:24 by kdezaphi          #+#    #+#             */
/*   Updated: 2015/03/07 11:25:31 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_cmd_sub_run(t_vm *vm, t_player *player, char *coding, int *jump)
{
	int		param[3];
	int		i;

	coding[3] = 2;
	*jump = ft_get_param(vm, player, param, coding);
	if (vm->verbose)
	{
		ft_printf("P %4d | sub r%d r%d r%d\n", player->num_proc,
			param[0], param[1], param[2]);
		ft_printf("ADV %d (%#06x -> %#06x) ", *jump, player->pc,
			(player->pc + *jump) % MEM_SIZE);
		i = -1;
		while (++i < *jump)
			ft_printf("%02x ", vm->arena[(player->pc + i) % MEM_SIZE]);
		ft_printf("\n");
	}
	param[0] = player->reg[param[0] - 1];
	param[1] = player->reg[param[1] - 1];
	player->reg[param[2] - 1] = param[0] - param[1];
	player->carry = player->reg[param[2] - 1];
}

void		ft_cmd_sub(t_vm *vm, t_player *player)
{
	char	*coding;
	int		jump;

	jump = 1;
	player->carry = 1;
	coding = ft_get_encoding_code(vm->arena[(player->pc + jump) % MEM_SIZE]);
	if (coding[0] == 'r' && coding[1] == 'r' && coding[2] == 'r'
		&& coding[3] == 0)
		ft_cmd_sub_run(vm, player, coding, &jump);
	else
		ft_corr_encoding(coding, &jump, 3, 2);
	free(coding);
	player->pc = (player->pc + jump) % MEM_SIZE;
}
