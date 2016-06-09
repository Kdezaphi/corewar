/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 15:22:00 by kdezaphi          #+#    #+#             */
/*   Updated: 2014/11/06 15:22:01 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*list;

	while (*alst != NULL)
	{
		(*del)((*alst)->content, (*alst)->content_size);
		list = *alst;
		free(*alst);
		*alst = NULL;
		*alst = list->next;
	}
	*alst = NULL;
	list = NULL;
}
