/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 14:12:57 by kdezaphi          #+#    #+#             */
/*   Updated: 2014/11/06 14:12:58 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*lstnew;

	lstnew = (t_list *)malloc(sizeof(t_list));
	if (lstnew)
	{
		if (content)
		{
			lstnew->content = malloc(content_size);
			lstnew->content = ft_memcpy(lstnew->content, content, content_size);
			lstnew->content_size = content_size;
		}
		else
		{
			lstnew->content = NULL;
			lstnew->content_size = 0;
		}
		lstnew->next = NULL;
	}
	return (lstnew);
}
