/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <kdezaphi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 20:14:09 by rankierm          #+#    #+#             */
/*   Updated: 2016/04/28 13:15:10 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

static void	ft_check_header_params(char *s, int lp)
{
	int		last_quotes;
	int		len;

	if (!s)
		ft_error("comments error, usage: \"[a-zA-Z0-9]\"", lp, ASM_EXIT);
	if (*s != '"')
		ft_error("comments error, usage: \"[a-zA-Z0-9]\"", lp, ASM_EXIT);
	len = (int)ft_strlen(s);
	last_quotes = ft_strchri(s + 1, '"');
	if (last_quotes == -1 || last_quotes != (len - 2))
		ft_error("comments error, usage: \"[a-zA-Z0-9]\"", lp, ASM_EXIT);
}

char		*ft_remove_quotes_header(char *s)
{
	return (ft_strsub(s, 1, ft_strlen(s) - 2));
}

void		ft_check_header(char **tab, t_asm *st_asm, int lp)
{
	if (ft_strequ(tab[0], NAME_CMD_STRING))
	{
		ft_check_header_params(tab[1], lp);
		// if (st_asm->header.name)
		// 	ft_error("name already defined", lp, ASM_EXIT);
		if (ft_strlen(tab[1]) > PROG_NAME_LENGTH)
			ft_error("name too long", lp, ASM_EXIT);
		st_asm->header.name = ft_remove_quotes_header(tab[1]);
	}
	else if (ft_strequ(tab[0], COMMENT_CMD_STRING))
	{
		ft_check_header_params(tab[1], lp);
		if (st_asm->header.comment)
			ft_error("description already defined", lp, ASM_EXIT);
		else if (ft_strlen(tab[1]) > COMMENT_LENGTH)
			ft_error("name too long", lp, ASM_EXIT);
		st_asm->header.comment = ft_remove_quotes_header(tab[1]);
	}
	else
		ft_error("header name not recognized", lp, ASM_EXIT);
}
