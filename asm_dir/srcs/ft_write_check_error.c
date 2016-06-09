/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_check_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamano <atamano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/23 14:55:37 by atamano           #+#    #+#             */
/*   Updated: 2015/02/23 14:55:38 by atamano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_check2_label2(t_list *label, char *str)
{
	if (str[0] == '%')
		str++;
	str++;
	while (label)
	{
		if (!ft_strcmp(str, ((t_label *)label->content)->name))
			return ;
		label = label->next;
	}
	ft_error("label not found", 0, ASM_EXIT);
}

void		ft_check2_label(t_list *label, t_list *list)
{
	int		i;

	while (list)
	{
		i = -1;
		while (((t_line *)list->content)->args[++i])
		{
			if (!ft_strncmp(((t_line *)list->content)->args[i], "%:", 2)
				|| !ft_strncmp(((t_line *)list->content)->args[i], ":", 1))
				ft_check2_label2(label, ((t_line *)list->content)->args[i]);
		}
		list = list->next;
	}
}

void		ft_check2_arguments(t_list *list)
{
	t_line	*line;
	int		i;

	while (list)
	{
		line = (t_line *)list->content;
		i = -1;
		while (line->args[++i])
		{
			if (line->args[i][0] == '%' && line->args[i][1] != ':'
				&& (!ft_isdigit(line->args[i][1])
					&& ((line->args[i][1] != '-' || (line->args[i][1] == '-'
						&& (!ft_isdigit(line->args[i][2])))))))
				ft_error("Lexical error", 0, ASM_EXIT);
		}
		list = list->next;
	}
}

void		ft_check_last_error(t_asm st_asm)
{
	ft_check2_label(st_asm.label, st_asm.list);
	ft_check2_arguments(st_asm.list);
}
