/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_ld.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 16:07:14 by kdezaphi          #+#    #+#             */
/*   Updated: 2015/03/07 10:37:46 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_cmd_ld_run(t_vm *vm, t_player *player, char *coding, int *jump)
{
	int		param[2];
	int		i;

	coding[3] = 4;
	*jump = ft_get_param(vm, player, param, coding);
	if (coding[0] == 'i')
		param[0] = ft_param(vm, player, param[0] % IDX_MOD, 4);
	if (vm->verbose)
	{
		ft_printf("P %4d | ld %d r%d\n", player->num_proc, param[0], param[1]);
		ft_printf("ADV %d (%#06x -> %#06x) ", *jump, player->pc,
			(player->pc + *jump) % MEM_SIZE);
		i = -1;
		while (++i < *jump)
			ft_printf("%02x ", vm->arena[(player->pc + i) % MEM_SIZE]);
		ft_printf("\n");
	}
	player->reg[param[1] - 1] = param[0];
	player->carry = player->reg[param[1] - 1];
}

void	ft_cmd_ld(t_vm *vm, t_player *player)
{
	char	*coding;
	int		jump;

	jump = 1;
	player->carry = 1;
	coding = ft_get_encoding_code(vm->arena[(player->pc + jump) % MEM_SIZE]);
	if ((coding[0] == 'd' || coding[0] == 'i') && coding[1] == 'r'
		&& coding[2] == 0 && coding[3] == 0)
		ft_cmd_ld_run(vm, player, coding, &jump);
	else
		ft_corr_encoding(coding, &jump, 2, 2);
	free(coding);
	player->pc = (player->pc + jump) % MEM_SIZE;
}

void	ft_cmd_lld_run(t_vm *vm, t_player *player, char *coding, int *jump)
{
	int		param[2];

	coding[3] = 4;
	*jump = ft_get_param(vm, player, param, coding);
	if (coding[0] == 'i')
		param[0] = ft_param(vm, player, param[0], 4);
	if (vm->verbose)
	{
		ft_printf("P %4d | lld: %d r%d\n", player->num_proc, param[0],
			param[1]);
		ft_printf("ADV %d (%#06x -> %#06x)\n", *jump, player->pc,
			(player->pc + *jump) % MEM_SIZE);
	}
	player->reg[param[1] - 1] = param[0];
	player->carry = player->reg[param[1] - 1];
}

void	ft_cmd_lld(t_vm *vm, t_player *player)
{
	char	*coding;
	int		jump;

	jump = 1;
	player->carry = 1;
	coding = ft_get_encoding_code(vm->arena[(player->pc + jump) % MEM_SIZE]);
	if ((coding[0] == 'd' || coding[0] == 'i') && coding[1] == 'r'
		&& coding[2] == 0 && coding[3] == 0)
		ft_cmd_lld_run(vm, player, coding, &jump);
	else
		ft_corr_encoding(coding, &jump, 2, 2);
	free(coding);
	player->pc = (player->pc + jump) % MEM_SIZE;
}
