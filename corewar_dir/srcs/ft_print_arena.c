/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_arena.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 09:43:34 by mgiraud-          #+#    #+#             */
/*   Updated: 2015/03/10 13:55:58 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			ft_get_color(t_vm *vm, int i)
{
	unsigned int	j;

	j = 0;
	while (j < vm->nb_player)
	{
		if (vm->info_player[j].num_player == vm->arena_player[i])
		{
			ft_printf("\x1b[%um", vm->info_player[j].color);
			return (1);
		}
		j++;
	}
	return (0);
}

void		ft_print_arena(t_vm *vm)
{
	int		i;
	int		color;

	ft_printf("\n");
	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_putchar('\n');
		color = ft_get_color(vm, i);
		ft_printf("%02x ", vm->arena[i]);
		if (color)
			ft_putstr("\x1b[0m");
		i++;
	}
	ft_printf("\n");
}

void		ft_print_arena_player(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_putchar('\n');
		ft_printf("%2d ", vm->arena_player[i]);
		i++;
	}
	ft_printf("\n");
}

void		ft_print_winner(t_vm *vm)
{
	int				i;
	int				j;
	int				k;

	i = -1;
	j = -1;
	k = 0;
	while (++i < (int)vm->nb_player)
	{
		if (vm->info_player[i].last_live > j)
		{
			j = vm->info_player[i].last_live;
			k = i;
		}
		if (j == vm->info_player[i].last_live)
		{
			if (vm->info_player[i].nb_live > vm->info_player[k].nb_live)
				k = i;
		}
		if (vm->verbose)
			ft_printf("%s do his last live during the %d cycle (%d lives \
during the last period)\n", vm->info_player[i].name,
			vm->info_player[i].last_live, vm->info_player[i].nb_live);
	}
	ft_printf("The winner is : %s\n", vm->info_player[k].name);
}
