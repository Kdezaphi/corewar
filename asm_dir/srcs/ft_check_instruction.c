/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_instruction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rankierm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 09:57:38 by rankierm          #+#    #+#             */
/*   Updated: 2015/03/11 16:27:39 by rankierm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

static void	ft_check_instruc_word(const char *s, t_line *line, t_op *op, int lp)
{
	int		i;
	int		flag;

	i = 0;
	flag = 1;
	while (flag && op[i].cmd)
	{
		if (ft_strequ(s, op[i].cmd))
		{
			line->opcode = ft_strdup(s);
			flag = 0;
		}
		i++;
	}
	if (flag)
		ft_error("wrong type instruction", lp, ASM_EXIT);
}

static int	ft_check_mask_arg(char arg_code, t_op *op, t_line *line, int i)
{
	int		*mask;
	int		ret;

	mask = ft_get_op_args_mask(op, line->opcode);
	ret = ((*(mask + i) & arg_code)) ? 1 : 0;
	return (ret);
}

static void	ft_check_instruc_args(char *args, t_line *line, t_op *op, int lp)
{
	int		i;
	char	**tmp;
	char	**tab;
	char	c;

	if (!(tab = ft_strsplit(args, ',')))
		ft_error("no arguments", lp, ASM_EXIT);
	i = ft_tablen(tab);
	if (i != ft_get_op_args_nb(op, line->opcode))
		ft_error("wrong number arguments", lp, ASM_EXIT);
	if (!(tmp = (char **)ft_memalloc(sizeof(char *) * i + 1)))
		ft_error("asm unexpected error: malloc#2 -> instruction", lp, ASM_EXIT);
	tmp[i] = NULL;
	while (i--)
	{
		tmp[i] = ft_strtrim(tab[i]);
		c = ft_replace_instruction_args(tmp[i][0], lp);
		if (!ft_check_mask_arg(c, op, line, i))
			ft_error("wrong type argument", lp, ASM_EXIT);
	}
	line->args = tmp;
	ft_free_2dtable(tab);
}

static void	ft_check_start_last_character(char *s, int lp)
{
	int		i;

	if (s)
	{
		i = ft_strlen(s);
		if (s[0] == ',')
			ft_error("startline character", lp, ASM_EXIT);
		if (s[i - 1] == ',')
			ft_error("endline character", lp, ASM_EXIT);
	}
}

void		ft_check_instruction(char **tab, t_asm *st_asm, int *p, int lp)
{
	t_line	line;
	char	**split_tab;
	int		i;

	if (!((t_header)st_asm->header).name)
		ft_error("no name defined", lp, ASM_EXIT);
	if (!((t_header)st_asm->header).comment)
		ft_error("no comment defined", lp, ASM_EXIT);
	if ((i = ft_check_label(tab, &st_asm->label, p)))
		if (!tab[1])
			return ;
	split_tab = (i) ? ft_split_first_word(tab[i]) : tab;
	ft_check_instruc_word(split_tab[0], &line, st_asm->op, lp);
	line.size_from_begin = *p;
	ft_check_start_last_character(split_tab[1], lp);
	ft_check_instruc_args(split_tab[1], &line, st_asm->op, lp);
	*p += ft_compute_instruction_size(&line, st_asm->op, lp);
	if (!st_asm->list)
		st_asm->list = ft_lstnew(&line, sizeof(t_line));
	else
		ft_lstaddlast(&(st_asm->list), ft_lstnew(&line, sizeof(t_line)));
	ft_free_2dtable(split_tab);
}
