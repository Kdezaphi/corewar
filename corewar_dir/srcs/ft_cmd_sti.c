/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_sti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/22 14:03:24 by kdezaphi          #+#    #+#             */
/*   Updated: 2015/03/07 11:30:39 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_cmd_sti_verbose(int *param, t_player *player, int *jump)
{
	ft_printf("P %4d | sti r%d %d %d\n", player->num_proc, param[0], param[1],
		param[2]);
	ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
		param[1], param[2], param[1] + param[2],
		player->pc + (param[1] % IDX_MOD + param[2] % IDX_MOD) % IDX_MOD);
	ft_printf("ADV %d (%#06x -> %#06x) ", *jump, player->pc,
		(player->pc + *jump) % MEM_SIZE);
}

static void	ft_cmd_sti_run2(t_vm *vm, t_player *player, int *param)
{
	int		diff;
	int		i;

	diff = player->pc + ((param[1] % IDX_MOD + param[2] % IDX_MOD) % IDX_MOD);
	if (diff > -4 && diff < 0)
	{
		ft_memcpy(&vm->arena[MEM_SIZE + diff], &param[0], -diff);
		param[0] = param[0] << (8 * -diff);
		ft_memcpy(&vm->arena[0], &param[0], 4 + diff);
	}
	else if (MEM_SIZE - diff < 4 && MEM_SIZE - diff > 0)
	{
		ft_memcpy(&vm->arena[diff], &param[0], MEM_SIZE - diff);
		param[0] = param[0] >> (8 * (MEM_SIZE - diff));
		ft_memcpy(&vm->arena[0], &param[0], 4 - (MEM_SIZE - diff));
	}
	else
		ft_memcpy(&vm->arena[(unsigned int)diff % MEM_SIZE], &param[0], 4);
	i = -1;
	while (++i < 4)
		ft_memcpy(&vm->arena_player[(player->pc + (param[1] % IDX_MOD + param[2]
			% IDX_MOD) % IDX_MOD + i) % MEM_SIZE], &player->num_player, 4);
}

static void	ft_cmd_sti_run(t_vm *vm, t_player *player, char *coding, int *jump)
{
	int		param[3];
	int		i;

	coding[3] = 2;
	*jump = ft_get_param(vm, player, param, coding);
	if (coding[1] == 'i')
		ft_memcpy(&param[1],
			&vm->arena[(player->pc + param[1] % IDX_MOD) % MEM_SIZE], 4);
	else if (coding[1] == 'r')
		param[1] = player->reg[param[1] - 1];
	if (coding[2] == 'r')
		param[2] = player->reg[param[2] - 1];
	if (vm->verbose)
	{
		ft_cmd_sti_verbose(param, player, jump);
		i = -1;
		while (++i < *jump)
			ft_printf("%02x ", vm->arena[(player->pc + i) % MEM_SIZE]);
		ft_printf("\n");
	}
	param[0] = player->reg[param[0] - 1];
	ft_memrev(&param[0], 4);
	ft_cmd_sti_run2(vm, player, param);
}

void		ft_cmd_sti(t_vm *vm, t_player *player)
{
	char	*coding;
	int		jump;

	jump = 1;
	coding = ft_get_encoding_code(vm->arena[(player->pc + jump) % MEM_SIZE]);
	if (coding[0] == 'r' && (coding[1] == 'r' || coding[1] == 'd'
		|| coding[1] == 'i') && (coding[2] == 'r' || coding[2] == 'd')
		&& coding[3] == 0)
		ft_cmd_sti_run(vm, player, coding, &jump);
	else
		ft_corr_encoding(coding, &jump, 3, 2);
	free(coding);
	player->pc = (player->pc + jump) % MEM_SIZE;
}
