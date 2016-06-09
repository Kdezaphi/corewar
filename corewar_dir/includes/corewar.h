/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <kdezaphi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 17:44:38 by mgiraud-          #+#    #+#             */
/*   Updated: 2016/04/28 11:34:17 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "ft_printf.h"
# include "op.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <SDL.h>
# include <SDL_ttf.h>

# define CYCLE_PER_SEC				1000
# define SEC						1000000

# define RECTANGLE_SIZE				20
# define WINDOW_Y_OFFSET			50
# define WINDOW_X_OFFSET			200
# define BLOCK_PLAYER_MARGIN_Y		80
# define BLOCK_GAME_INFO_MARGIN_Y	400
# define OPTION_FONT_SIZE			12
# define PLAYER_FONT_SIZE			30
# define CYCLE_DELTA_STR			"50"

typedef	enum			e_colors
{
	RESET = 0,
	RED = 31,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
}						t_colors;

typedef	enum			e_cmd_names
{
	NONE,
	LIVE,
	LD,
	ST,
	ADD,
	SUB,
	AND,
	OR,
	XOR,
	ZJMP,
	LDI,
	STI,
	FORK,
	LLD,
	LLDI,
	LFORK,
	AFF,
}						t_cmd_names;

typedef struct			s_texture
{
	SDL_Surface			*surface;
	SDL_Texture			*texture;
	SDL_Rect			rect;
	SDL_Color			color;
	int					tex_w;
	int					tex_h;
}						t_texture;

typedef struct			s_sdl
{
	SDL_Window			*pwindow;
	SDL_Event			event;
	TTF_Font			*font;
	TTF_Font			*font2;
	SDL_Renderer		*renderer;
	int					arena_size;
	int					dump_byte;
}						t_sdl;

typedef struct			s_player
{
	char				prog_name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	char				prog[CHAMP_MAX_SIZE + 1];
	int					reg[REG_NUMBER];
	unsigned int		prog_size;
	char				carry;
	char				live;
	unsigned int		pc;
	unsigned int		next_cycle_inst;
	int					num_player;
	int					num_proc;
}						t_player;

typedef struct			s_info_player
{
	int					num_player;
	int					last_live;
	int					nb_live;
	unsigned int		color;
	char				name[PROG_NAME_LENGTH + 1];
	int					nb_bytes;
}						t_info_player;

typedef struct			s_vm
{
	unsigned int		nb_player;
	t_list				*player;
	struct s_bytecode	*bytecode;
	unsigned int		finished;
	unsigned int		paused;
	int					cycle_to_die;
	unsigned int		cur_cycle;
	unsigned char		*arena;
	int					*arena_player;
	unsigned int		graphical_mode;
	unsigned int		check;
	unsigned int		next_check_to_die;
	unsigned int		last_cycle_dec;
	char				winner[PROG_NAME_LENGTH + 1];
	t_info_player		info_player[MAX_PLAYERS];
	t_sdl				sdl;
	int					dump_cycle;
	int					nb_proc;
	int					verbose;
	int					display_proc_list;
}						t_vm;

typedef struct			s_bytecode
{
	t_cmd_names			byte;
	unsigned int		nb_cycle;
	void				(*f)(t_vm *vm, t_player *);
}						t_bytecode;

typedef union			u_param
{
	int					param_i;
	char				param_s[4];
}						t_param;

void					ft_usage_error(void);
void					ft_verif_binfile(char *path, t_player *player);
void					my_error(char *str, int is_perror);
int						ft_is_number(char *str);
void					ft_initialize_vm(t_vm *vm);
void					ft_make_arena(t_vm *vm, int	nb_player);
void					ft_memrev(void *ptr, size_t n);
int						ft_param(t_vm *vm, t_player *player, int jump,
	int size);
int						ft_get_param(t_vm *vm, t_player *player,
	int *param, char *c);
void					ft_print_arena(t_vm *vm);
void					ft_corr_encoding(char *c, int *j, int arg, int lab);
void					ft_cmd_ld(t_vm *vm, t_player *player);
void					ft_cmd_lld(t_vm *vm, t_player *player);
void					ft_cmd_live(t_vm *vm, t_player *player);
void					ft_cmd_st(t_vm *vm, t_player *player);
void					ft_cmd_add(t_vm *vm, t_player *player);
void					ft_cmd_sub(t_vm *vm, t_player *player);
void					ft_cmd_and(t_vm *vm, t_player *player);
void					ft_cmd_or(t_vm *vm, t_player *player);
void					ft_cmd_xor(t_vm *vm, t_player *player);
void					ft_cmd_zjmp(t_vm *vm, t_player *player);
void					ft_cmd_ldi(t_vm *vm, t_player *player);
void					ft_cmd_lldi(t_vm *vm, t_player *player);
void					ft_cmd_sti(t_vm *vm, t_player *player);
void					ft_cmd_fork(t_vm *vm, t_player *player);
void					ft_cmd_lfork(t_vm *vm, t_player *player);
void					ft_cmd_aff(t_vm *vm, t_player *player);
char					*ft_get_encoding_code(char c);
void					ft_set_arena_player(t_vm *vm, int jump,
	t_player *player);
void					ft_print_arena_player(t_vm *vm);
void					ft_print_winner(t_vm *vm);
void					ft_initiate_window(t_vm *vm);
void					ft_destroy_window(t_vm *vm);
void					ft_graphical_mode(t_vm *vm, double to_wait);
void					ft_new_player(t_vm *vm, char *name, int num,
	int *cur_player);
void					ft_check_to_die(t_vm *vm);
void					ft_print_player_sum(t_vm *vm, int i);
void					ft_print_player_last_live(t_vm *vm, int i);
void					ft_print_player_cur_live(t_vm *vm, int i);
void					ft_print_player_cycle_to_die(t_vm *vm);
void					ft_print_player_cycle_delta(t_vm *vm);
void					ft_fill_sdl_color(SDL_Color *color, int r, int g,
	int b);
void					ft_print_pc(t_vm *vm);
void					ft_print_cycle_limit(t_vm *vm);
void					ft_print_cur_cycle(t_vm *vm);
void					ft_get_player_color(t_vm *vm, int i, int *color);
void					ft_get_player_color_by_player(t_vm *vm, int i,
	int *color);
void					ft_dump_byte(t_vm *vm, int i, SDL_Rect *byte);
void					ft_print_players(t_vm *vm);
void					ft_dump_byte(t_vm *vm, int i, SDL_Rect *byte);
void					ft_print_datas(t_vm *vm);
int						ft_kill_player(t_vm *vm, int num_player);
void					ft_update_live_player(t_vm *vm);
void					ft_display_proc(t_vm *vm);

#endif
