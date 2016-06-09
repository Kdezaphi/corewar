/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instantiate_vm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <kdezaphi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 17:13:49 by mgiraud-          #+#    #+#             */
/*   Updated: 2016/04/27 12:10:48 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				ft_make_arena_player(t_vm *vm, t_player *player)
{
	unsigned int	i;

	i = player->pc;
	while (i < player->pc + player->prog_size)
	{
		vm->arena_player[i] = player->num_player;
		i++;
	}
}

void				ft_make_arena(t_vm *vm, int nb_player)
{
	t_list		*list;
	t_player	*player;
	int			i;

	list = vm->player;
	vm->nb_proc = 0;
	i = 0;
	while (list != NULL)
	{
		vm->nb_proc++;
		player = (t_player*)list->content;
		if ((int)player->prog_size > MEM_SIZE / nb_player)
		{
			ft_printf_fd(2, "Error: Champion '%s' is too big for the arena\
				\n", player->prog_name);
			exit(EXIT_FAILURE);
		}
		ft_memcpy(&(vm->arena[MEM_SIZE * i / nb_player]),
			player->prog, player->prog_size);
		player->pc = MEM_SIZE * i / nb_player;
		player->num_proc = vm->nb_proc;
		ft_make_arena_player(vm, player);
		list = list->next;
		i++;
	}
}

static t_bytecode	ft_pbc(char c, void (*f)(t_vm *, t_player *),
	unsigned int nb_cycle)
{
	t_bytecode by;

	by.byte = c;
	by.f = f;
	by.nb_cycle = nb_cycle;
	return (by);
}

static void			ft_populate_bytecode_array(t_vm *vm)
{
	vm->bytecode[0] = ft_pbc(NONE, NULL, 0);
	vm->bytecode[1] = ft_pbc(LIVE, &ft_cmd_live, 10);
	vm->bytecode[2] = ft_pbc(LD, &ft_cmd_ld, 5);
	vm->bytecode[3] = ft_pbc(ST, &ft_cmd_st, 5);
	vm->bytecode[4] = ft_pbc(ADD, &ft_cmd_add, 10);
	vm->bytecode[5] = ft_pbc(SUB, &ft_cmd_sub, 10);
	vm->bytecode[6] = ft_pbc(AND, &ft_cmd_and, 6);
	vm->bytecode[7] = ft_pbc(OR, &ft_cmd_or, 6);
	vm->bytecode[8] = ft_pbc(XOR, &ft_cmd_xor, 6);
	vm->bytecode[9] = ft_pbc(ZJMP, &ft_cmd_zjmp, 20);
	vm->bytecode[10] = ft_pbc(LDI, &ft_cmd_ldi, 25);
	vm->bytecode[11] = ft_pbc(STI, &ft_cmd_sti, 25);
	vm->bytecode[12] = ft_pbc(FORK, &ft_cmd_fork, 800);
	vm->bytecode[13] = ft_pbc(LLD, &ft_cmd_lld, 10);
	vm->bytecode[14] = ft_pbc(LLDI, &ft_cmd_lldi, 50);
	vm->bytecode[15] = ft_pbc(LFORK, &ft_cmd_lfork, 1000);
	vm->bytecode[16] = ft_pbc(AFF, &ft_cmd_aff, 2);
}

void				ft_initialize_vm(t_vm *vm)
{
	vm->display_proc_list = 0;
	vm->dump_cycle = -1;
	vm->nb_player = 0;
	vm->finished = 0;
	vm->cur_cycle = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->player = NULL;
	vm->graphical_mode = 0;
	vm->next_check_to_die = CYCLE_TO_DIE;
	vm->last_cycle_dec = 0;
	vm->paused = 0;
	vm->verbose = 0;
	vm->sdl.arena_size = sqrt(MEM_SIZE) * 20;
	vm->sdl.dump_byte = 0;
	ft_bzero(vm->winner, PROG_NAME_LENGTH + 1);
	vm->arena = (unsigned char*)malloc(sizeof(unsigned char) * MEM_SIZE);
	ft_bzero(vm->arena, sizeof(unsigned char) * MEM_SIZE);
	vm->arena_player = (int*)malloc(sizeof(int) * MEM_SIZE);
	vm->bytecode = (t_bytecode*)malloc(sizeof(t_bytecode) * 17);
	ft_bzero(vm->arena, PROG_NAME_LENGTH + 1);
	ft_populate_bytecode_array(vm);
}
