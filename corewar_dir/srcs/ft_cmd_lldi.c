/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_lldi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 12:59:04 by kdezaphi          #+#    #+#             */
/*   Updated: 2015/03/09 12:59:07 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_cmd_lldi_verbose(t_player *player, char *coding,
	int *jump, int *param)
{
	ft_printf("P %4d | lldi ", player->num_proc);
	if (coding[0] == 'r')
		ft_printf("r%d ", param[0]);
	else
		ft_printf("%d ", param[0]);
	if (coding[1] == 'r')
		ft_printf("r%d ", param[1]);
	else
		ft_printf("%d ", param[1]);
	ft_printf("r%d\n", param[2]);
	ft_printf("ADV %d (%#06x -> %#06x) ", *jump, player->pc,
		(player->pc + *jump) % MEM_SIZE);
}

static void	ft_cmd_lldi_run(t_vm *vm, t_player *player, char *coding, int *jump)
{
	int		param[3];
	int		i;

	coding[3] = 2;
	*jump = ft_get_param(vm, player, param, coding);
	if (vm->verbose)
	{
		ft_cmd_lldi_verbose(player, coding, jump, param);
		i = -1;
		while (++i < *jump)
			ft_printf("%02x \n", vm->arena[(player->pc + i) % MEM_SIZE]);
	}
	if (coding[0] == 'r')
		param[0] = player->reg[param[0] - 1];
	else if (coding[0] == 'i')
	{
		ft_memcpy(&param[0], &vm->arena[(player->pc + param[0]) % MEM_SIZE], 4);
		ft_memrev(&param[0], 4);
	}
	if (coding[1] == 'r')
		param[1] = player->reg[param[1] - 1];
	player->reg[param[2] - 1] = ft_param(vm, player,
		(param[0] + param[1]) % MEM_SIZE, 4);
}

void		ft_cmd_lldi(t_vm *vm, t_player *player)
{
	char	*coding;
	int		jump;

	jump = 1;
	coding = ft_get_encoding_code(vm->arena[(player->pc + jump) % MEM_SIZE]);
	if ((coding[0] == 'r' || coding[0] == 'd' || coding[0] == 'i')
		&& (coding[1] == 'r' || coding[1] == 'd') && coding[2] == 'r'
		&& coding[3] == 0)
		ft_cmd_lldi_run(vm, player, coding, &jump);
	else
		ft_corr_encoding(coding, &jump, 3, 2);
	free(coding);
	player->pc = (player->pc + jump) % MEM_SIZE;
}
