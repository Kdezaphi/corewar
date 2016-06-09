/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_ldi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 11:45:29 by kdezaphi          #+#    #+#             */
/*   Updated: 2015/03/07 11:54:58 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_cmd_ldi_verbose(t_player *player, int *jump, int *param)
{
	ft_printf("P %4d | ldi %d %d r%d\n", player->num_proc, param[0], param[1],
		param[2]);
	ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
		param[0], param[1], param[0] + param[1],
		player->pc + (param[0] % IDX_MOD + param[1] % IDX_MOD) % IDX_MOD);
	ft_printf("ADV %d (%#06x -> %#06x) ", *jump, player->pc,
		(player->pc + *jump) % MEM_SIZE);
}

static void	ft_cmd_ldi_run(t_vm *vm, t_player *player, char *coding, int *jump)
{
	int		param[3];
	int		i;

	coding[3] = 2;
	*jump = ft_get_param(vm, player, param, coding);
	if (coding[0] == 'r')
		param[0] = player->reg[param[0] - 1];
	else if (coding[0] == 'i')
		param[0] = ft_param(vm, player, param[0] % IDX_MOD, 4);
	if (coding[1] == 'r')
		param[1] = player->reg[param[1] - 1];
	if (vm->verbose)
	{
		ft_cmd_ldi_verbose(player, jump, param);
		i = -1;
		while (++i < *jump)
			ft_printf("%02x ", vm->arena[(player->pc + i) % MEM_SIZE]);
		ft_printf("\n");
	}
	player->reg[param[2] - 1] = ft_param(vm, player,
		((param[0] % IDX_MOD + param[1] % IDX_MOD) % IDX_MOD) % MEM_SIZE, 4);
}

void		ft_cmd_ldi(t_vm *vm, t_player *player)
{
	char	*coding;
	int		jump;

	jump = 1;
	coding = ft_get_encoding_code(vm->arena[(player->pc + jump) % MEM_SIZE]);
	if ((coding[0] == 'r' || coding[0] == 'd' || coding[0] == 'i')
		&& (coding[1] == 'r' || coding[1] == 'd') && coding[2] == 'r'
		&& coding[3] == 0)
		ft_cmd_ldi_run(vm, player, coding, &jump);
	else
		ft_corr_encoding(coding, &jump, 3, 2);
	free(coding);
	player->pc = (player->pc + jump) % MEM_SIZE;
}
