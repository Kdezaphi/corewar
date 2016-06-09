CC = gcc -O3

CFLAGS = -Wall -Wextra -Werror -I ../ft_printf/includes/ -I includes -I./SDL2.framework/Headers -I./SDL2_ttf.framework/Headers -I../includes

SRC =	corewar.c\
		ft_errors.c\
		ft_verif_binfile.c\
		ft_helpers.c\
		ft_instantiate_vm.c\
		ft_cmd_fork.c\
		ft_print_arena.c\
		get_cmd_arguments.c\
		ft_param_access.c\
		ft_cmd_ld.c\
		ft_cmd_live.c\
		ft_cmd_st.c\
		ft_cmd_add.c\
		ft_cmd_sub.c\
		ft_cmd_and.c\
		ft_cmd_or.c\
		ft_cmd_xor.c\
		ft_cmd_zjmp.c\
		ft_cmd_ldi.c\
		ft_cmd_sti.c\
		ft_cmd_aff.c\
		ft_window.c\
		ft_instantiate_player.c\
		ft_check_cycle_to_die.c\
		ft_window2.c\
		ft_window3.c\
		ft_window4.c\
		ft_window5.c\
		ft_check_cycle_to_die2.c\
		ft_cmd_lldi.c\
		ft_display_proc.c

NAME = corewar

LIB = ../ft_printf/libftprintf.a  -F ./ -framework SDL2 -framework SDL2_ttf

SRCS = $(addprefix srcs/, $(SRC))

OBJ = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(LIB) $(OBJ) -o $(NAME)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f ../$(NAME)

re: fclean all

.PHONY: clean fclean re
