/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 18:04:36 by kdezaphi          #+#    #+#             */
/*   Updated: 2015/03/07 10:40:25 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_param(t_vm *vm, t_player *player, int jump, int size)
{
	t_param	param;
	int		diff;

	if (vm->arena[(player->pc + jump) % MEM_SIZE] > 127)
		param.param_i = -1;
	else
		param.param_i = 0;
	diff = player->pc + jump;
	if (diff > -size && diff < 0)
	{
		ft_memcpy(param.param_s, &vm->arena[MEM_SIZE + diff], -diff);
		ft_memcpy(&param.param_s[size + diff], &vm->arena[0], size + diff);
	}
	else if (MEM_SIZE - diff < size && MEM_SIZE - diff > 0)
	{
		ft_memcpy(param.param_s, &vm->arena[diff], MEM_SIZE - diff);
		ft_memcpy(&param.param_s[size - (MEM_SIZE - diff)],
			&vm->arena[0], size - (MEM_SIZE - diff));
	}
	else
		ft_memcpy(&param.param_i, &vm->arena[(player->pc + jump)
			% MEM_SIZE], size);
	ft_memrev(&param.param_i, size);
	return (param.param_i);
}

int		ft_get_param(t_vm *vm, t_player *player, int *param, char *coding)
{
	int		i;
	int		jump;

	i = 0;
	jump = 2;
	while (coding[i] && i < 3)
	{
		if (coding[i] == 'r')
		{
			param[i] = ft_param(vm, player, jump, 1);
			jump++;
		}
		else if (coding[i] == 'i')
		{
			param[i] = ft_param(vm, player, jump, 2);
			jump += 2;
		}
		else if (coding[i] == 'd')
		{
			param[i] = ft_param(vm, player, jump, coding[3]);
			jump += coding[3];
		}
		i++;
	}
	return (jump);
}
