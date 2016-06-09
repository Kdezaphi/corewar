/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_or.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 14:09:29 by kdezaphi          #+#    #+#             */
/*   Updated: 2015/03/10 10:14:37 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_cmd_or_verbose(t_vm *vm, t_player *player, int *jump, int *param)
{
	int		i;

	if (vm->verbose)
	{
		ft_printf("P %4d | or %d %d r%d\n", player->num_proc, param[0],
			param[1], param[2]);
		ft_printf("ADV %d (%#06x -> %#06x) ", *jump, player->pc,
			(player->pc + *jump) % MEM_SIZE);
		i = -1;
		while (++i < *jump)
			ft_printf("%02x ", vm->arena[(player->pc + i) % MEM_SIZE]);
		ft_printf("\n");
	}
}

static void	ft_cmd_or_run(t_vm *vm, t_player *player, char *coding, int *jump)
{
	int		param[3];
	int		i;

	coding[3] = 4;
	*jump = ft_get_param(vm, player, param, coding);
	i = -1;
	while (++i < 2)
		if (coding[i] == 'r')
			param[i] = player->reg[param[i] - 1];
		else if (coding[i] == 'i')
			param[i] = ft_param(vm, player, param[i] % IDX_MOD, 4);
	ft_cmd_or_verbose(vm, player, jump, param);
	player->reg[param[2] - 1] = param[0] | param[1];
	player->carry = player->reg[param[2] - 1];
}

void		ft_cmd_or(t_vm *vm, t_player *player)
{
	char	*coding;
	int		jump;

	jump = 1;
	player->carry = 1;
	coding = ft_get_encoding_code(vm->arena[(player->pc + jump) % MEM_SIZE]);
	if ((coding[0] == 'r' || coding[0] == 'd' || coding[0] == 'i')
		&& (coding[1] == 'r' || coding[1] == 'd' || coding[1] == 'i')
		&& coding[2] == 'r' && coding[3] == 0)
		ft_cmd_or_run(vm, player, coding, &jump);
	else
		ft_corr_encoding(coding, &jump, 3, 2);
	free(coding);
	player->pc = (player->pc + jump) % MEM_SIZE;
}
