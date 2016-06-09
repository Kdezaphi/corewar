/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cycle_to_die2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 16:50:46 by mgiraud-          #+#    #+#             */
/*   Updated: 2015/03/10 08:56:54 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_kill_player(t_vm *vm, int num_player)
{
	t_list		*list;
	t_player	*player;

	list = vm->player;
	while (list != NULL)
	{
		player = (t_player *)list->content;
		if (player->num_player == num_player)
			return (0);
		list = list->next;
	}
	return (1);
}

void	ft_update_live_player(t_vm *vm)
{
	t_list		*list;
	t_player	*player;

	list = vm->player;
	while (list != NULL)
	{
		player = (t_player*)list->content;
		if (player)
			player->live = 0;
		list = list->next;
	}
}
