/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdbladd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 16:50:14 by kdezaphi          #+#    #+#             */
/*   Updated: 2014/11/27 17:54:45 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstdbladd(t_list_dbl *insert, t_list_dbl *new)
{
	t_list_dbl	*list;

	list = insert->prev;
	new->next = insert;
	new->prev = list;
	list->next = new;
	insert->prev = new;
}
