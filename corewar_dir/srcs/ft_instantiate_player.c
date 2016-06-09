/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instantiate_player.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <kdezaphi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/22 11:54:19 by mgiraud-          #+#    #+#             */
/*   Updated: 2016/04/28 17:18:42 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_check_for_number(int *number, t_vm *vm, int *cur_player)
{
	int	i;

	i = 0;
	while (i < *cur_player)
	{
		if (vm->info_player[i].num_player == *number || *number == 0)
		{
			*number = *number - 1;
			ft_check_for_number(number, vm, cur_player);
		}
		i++;
	}
}

static void	ft_fill_player_struc(t_player *player, char *name, int number)
{
	player->reg[0] = number;
	player->carry = 1;
	player->next_cycle_inst = 0;
	player->num_player = number;
	ft_verif_binfile(name, player);
}

static void	ft_new_info_player(t_vm *vm, int *cur_player, t_player *player,
	int number)
{
	vm->nb_player++;
	vm->info_player[*cur_player - 1].num_player = number;
	vm->info_player[*cur_player - 1].nb_live = 0;
	vm->info_player[*cur_player - 1].color = (31 - 1 + *cur_player);
	vm->info_player[*cur_player - 1].nb_bytes = 0;
	vm->info_player[*cur_player - 1].last_live = 0;
	ft_bzero(vm->info_player[*cur_player - 1].name, PROG_NAME_LENGTH + 1);
	ft_memcpy(vm->info_player[*cur_player - 1].name, player->prog_name,
		PROG_NAME_LENGTH);
	ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\")\n",
		vm->nb_player, player->prog_size, player->prog_name, player->comment);
}

void		ft_new_player(t_vm *vm, char *name, int number, int *cur_player)
{
	t_player	*player;
	t_list		*cur;

	if (*cur_player + 1 > MAX_PLAYERS)
		my_error("Too much player\n", 0);
	if (!(player = (t_player *)malloc(sizeof(t_player))))
		my_error("corewar", 1);
	ft_check_for_number(&number, vm, cur_player);
	ft_fill_player_struc(player, name, number);
	if (!(cur = ft_lstnew(player, sizeof(t_player))))
		my_error("corewar", 1);
	free(player);
	if (vm->player == NULL)
		vm->player = cur;
	else
		ft_lstaddlast(&vm->player, cur);
	*cur_player = *cur_player + 1;
	ft_new_info_player(vm, cur_player, player, number);
}
