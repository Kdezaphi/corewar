/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_asm_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rankierm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 14:20:34 by rankierm          #+#    #+#             */
/*   Updated: 2015/02/23 19:14:05 by rankierm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

t_op	*ft_create_op(void)
{
	t_op	*ret;

	ret = (t_op *)ft_memalloc(sizeof(t_op) * 17);
	ft_init_op(ret);
	return (ret);
}

void	ft_free_header(t_header *header)
{
	free(header->name);
	header->name = NULL;
	free(header->comment);
	header->comment = NULL;
}

void	ft_t_asm_free(t_asm *st_asm)
{
	ft_free_header(&st_asm->header);
	free(st_asm->file_name);
	free(st_asm->op);
}

void	ft_t_asm_init(t_asm *st_asm)
{
	st_asm->file_name = NULL;
	st_asm->label = NULL;
	st_asm->list = NULL;
	st_asm->op = ft_create_op();
}
