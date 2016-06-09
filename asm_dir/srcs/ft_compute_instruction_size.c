/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compute_instruction_size.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rankierm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 13:31:51 by rankierm          #+#    #+#             */
/*   Updated: 2015/02/23 15:13:16 by rankierm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

int			ft_replace_instruction_args(t_arg_type c, int lp)
{
	if (c == 'r')
		return (T_REG);
	else if (c == DIRECT_CHAR)
		return (T_DIR);
	else if (ft_isdigit(c) || c == LABEL_CHAR || c == '-')
		return (T_IND);
	else
		ft_error("wrong type argument", lp, ASM_EXIT);
	return (0);
}

static int	ft_arg_size(t_line *line, int label_size, int args_nb, int lp)
{
	int			size;
	int			i;
	t_arg_type	t;

	size = 0;
	i = 0;
	while (i < args_nb)
	{
		t = line->args[i][0];
		if (ft_replace_instruction_args(t, lp) & T_DIR)
			size += label_size;
		else if (ft_replace_instruction_args(t, lp) & T_IND)
			size += 2;
		else if (ft_replace_instruction_args(t, lp) & T_REG)
		{
			if (ft_atoi((line->args[i]) + 1) < 1 ||
				ft_atoi((line->args[i]) + 1) > 16)
				ft_error("incorrect register number", lp, ASM_EXIT);
			size++;
		}
		else
			ft_error("asm, bag arugment, --- not expected", lp, ASM_EXIT);
		i++;
	}
	return (size);
}

int			ft_compute_instruction_size(t_line *line, t_op *op, int lp)
{
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (op[i].cmd)
	{
		if (ft_strequ(op[i].cmd, line->opcode))
		{
			size++;
			if (op[i].encoding)
				size++;
			size += ft_arg_size(line, op[i].label_size, op[i].args_nb, lp);
		}
		i++;
	}
	return (size);
}
