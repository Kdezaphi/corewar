CC = gcc -g3

CFLAGS = -Wall -Wextra -Werror -I ../ft_printf/includes/ -I ./includes -I../includes

SRC =	asm.c							\
		ft_check_header.c				\
		ft_check_label.c				\
		ft_check_instruction.c			\
		ft_compute_instruction_size.c	\
		ft_isblank.c					\
		ft_op_utils.c					\
		ft_error.c						\
		ft_first_gnl.c					\
		ft_free_2dtable.c				\
		ft_open_file.c					\
		ft_puttab.c						\
		ft_remove_blanks_and_semic.c	\
		ft_split_first_word.c			\
		ft_strchri.c					\
		ft_strsplitblank.c				\
		ft_t_asm_utils.c				\
		ft_write_arguments.c  			\
		ft_write_header.c 				\
		ft_write_to_file.c 				\
		ft_write_get_conditions.c       \
		ft_write_binaries_util.c        \
		ft_write_check_error.c  		\

NAME = asm

LIB = ../ft_printf/libftprintf.a

SRCS = $(addprefix srcs/, $(SRC))

OBJ = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(LIB) $(OBJ) -o $(NAME)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@ rm -f $(OBJ)

fclean: clean
	@ rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
