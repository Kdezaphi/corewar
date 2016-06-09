/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_proc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/10 09:54:05 by mgiraud-          #+#    #+#             */
/*   Updated: 2015/03/10 10:02:27 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_display_proc(t_vm *vm)
{
	t_list		*cur;
	t_player	*cur_player;

	cur = vm->player;
	ft_printf("%s\n", "------------START------------");
	while (cur != NULL)
	{
		cur_player = (t_player *)cur->content;
		ft_printf("Processus %d owned by %s (%d) ", cur_player->num_proc,
			cur_player->prog_name, cur_player->num_player);
		if (cur_player->live)
			ft_printf("says is alive\n");
		else
			ft_printf("doesn't say is alive\n");
		cur = cur->next;
	}
	ft_printf("%s\n", "-------------END-------------");
}
