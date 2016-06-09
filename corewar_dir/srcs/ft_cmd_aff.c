/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_aff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/22 22:51:59 by mgiraud-          #+#    #+#             */
/*   Updated: 2015/03/07 11:46:31 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_cmd_aff_run(t_vm *vm, t_player *player, char *coding, int *jump)
{
	unsigned char	c;
	int				param;

	coding[3] = 2;
	*jump = ft_get_param(vm, player, &param, coding);
	param = player->reg[param - 1];
	c = (unsigned int)param % 256;
	write(1, &c, 1);
}

void		ft_cmd_aff(t_vm *vm, t_player *player)
{
	char	*coding;
	int		jump;

	jump = 1;
	coding = ft_get_encoding_code(vm->arena[(player->pc + jump) % MEM_SIZE]);
	if (coding[0] == 'r' && coding[1] == 0 && coding[2] == 0 && coding[3] == 0)
		ft_cmd_aff_run(vm, player, coding, &jump);
	else
		ft_corr_encoding(coding, &jump, 1, 2);
	free(coding);
	player->pc = (player->pc + jump) % MEM_SIZE;
}
