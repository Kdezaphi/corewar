/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rankierm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 15:49:07 by rankierm          #+#    #+#             */
/*   Updated: 2015/02/23 19:01:49 by rankierm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <errno.h>
# include <string.h>
# include <errno.h>
# include "ft_printf.h"
# include "get_next_line.h"
# include "op.h"

# define ASM_EXIT 1
# define ASM_NON_EXIT 0

typedef struct	s_op
{
	char		*cmd;
	int			args_nb;
	int			args_mask[3];
	int			opcode;
	int			cycles;
	char		*description;
	int			encoding;
	int			carry;
	int			label_size;
}				t_op;

/*
** Nom de chaque label avec sa position dans le fichier
*/

typedef struct	s_label
{
	char		*name;
	int			position;
}				t_label;

/*
** Ligne du fichier
*/

typedef struct	s_line
{
	char		*opcode;
	char		**args;
	int			size_from_begin;
}				t_line;

typedef struct	s_header
{
	char		*name;
	char		*comment;
	int			prog_size;
}				t_header;

/*
** Structure globale
*/

typedef struct	s_asm
{
	char		*file_name;
	t_header	header;
	t_list		*label;
	t_list		*list;
	t_op		*op;
}				t_asm;

/*
** Prototypes
*/

void			ft_error(char *s, int line_position, char asm_exit);
int				ft_first_gnl(int fd, t_asm *st_asm);
int				ft_open_file(char *file, t_asm *st_asm);
void			ft_write_arguments(int fd, t_list *list, t_list *label);
void			ft_write_program(int fd, t_asm *st_asm);
void			ft_convert_file(t_asm *st_asm);
int				ft_get_label_size(char *str);
int				ft_has_encoding(char *opcode);
int				ft_write_opcode(int fd, char *str);
int				ft_write_opcode2(int fd, char *str);
void			ft_encode_args(char *c, char *str, int place);
void			ft_write_header(int fd, t_asm *st_asm);
void			ft_write_encoding(int fd, char **args, char *opcode);
void			ft_write_blank(int len, int fd);
int				ft_create_cor(t_asm *st_asm);
char			*ft_remove_blanks_and_semic(char *s);
int				ft_check_label(char **tab, t_list **label, int *position);
int				ft_check_label_word(const char *s);
void			ft_check_header(char **tab, t_asm *st_asm, int line_position);
void			ft_check_instruction(char **tab, t_asm *st_asm, int *p, int lp);
void			ft_t_asm_init(t_asm *st_asm);
void			ft_t_asm_free(t_asm *st_asm);
void			ft_init_op(t_op *t);
int				ft_compute_instruction_size(t_line *line, t_op *op, int lp);
void			ft_write_int(int fd, int num);
void			ft_write_oct(int fd, int num);
int				rev_int(int nb);
char			**ft_split_first_word(char *line);
char			**ft_split_first_word2(char *line);
int				ft_replace_instruction_args(t_arg_type c, int lp);
int				ft_get_op_args_nb(t_op *op, char *ref);
int				*ft_get_op_args_mask(t_op *op, char *ref);
void			ft_check2_label(t_list *label, t_list *list);
void			ft_check_last_error(t_asm st_asm);

/*
** Libft ++
*/
char			*ft_reverse_chr(char *s, int c);
int				ft_isblank(int c);
void			ft_free_2dtable(char **t);
int				ft_strchri(char *s, unsigned char c);
char			**ft_strsplitblank(char const *s);
void			ft_puttab(char **tab);
int				ft_tablen(char **tab);

#endif
