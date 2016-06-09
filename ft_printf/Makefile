# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdezaphi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/11 08:47:42 by kdezaphi          #+#    #+#              #
#    Updated: 2015/02/13 16:38:28 by kdezaphi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	ft_islower.c ft_isprint.c ft_isupper.c ft_itoa.c ft_memalloc.c ft_memccpy.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c  \
	ft_nblen.c ft_putchar_fd.c ft_putchar.c ft_putendl_fd.c ft_putendl.c \
	ft_putnbr_fd.c ft_putnbr.c ft_putstr_fd.c ft_putstr.c ft_strcat.c ft_strchr.c \
	ft_strclr.c	ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c \
	ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c \
	ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c \
	ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c \
	ft_tolower.c ft_toupper.c ft_lstadd.c ft_lstaddlast.c ft_lstdbladd_first.c \
	ft_lstdbladd_last.c ft_lstdbladd.c ft_lstdblnew.c ft_lstdel.c ft_lstdelone.c \
	ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_backslash.c ft_bintoint.c ft_flags.c \
	ft_llbtoa.c ft_lltoa.c ft_padpos.c ft_printf.c ft_type.c ft_typec.c ft_typed.c \
	ft_typenumeric.c ft_typeo.c ft_types.c ft_typestr.c ft_typeu.c ft_typewc.c \
	ft_typews.c ft_typex.c ft_printf_fd.c get_next_line.c ft_dup_join.c
SRC_DIR = ./sources/

OBJ = $(SRC:.c=.o)
INC = -I ./includes

CC = gcc
CFLAGS = -Wall -Werror -Wextra -O3

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rc $(NAME) $(OBJ)
	@echo "\033[32mArchive $(NAME) compilée avec succès\033[0m"

%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -f $(OBJ)

proper: all clean

fclean: clean
	@rm -f $(NAME)

re: fclean all
