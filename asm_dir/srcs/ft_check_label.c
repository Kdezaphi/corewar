/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_label.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rankierm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 20:10:10 by rankierm          #+#    #+#             */
/*   Updated: 2015/02/23 19:36:18 by rankierm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

int		ft_check_label_word(const char *s)
{
	int		i;
	int		nb_2dots;

	if (!s)
		return (0);
	nb_2dots = 0;
	i = 0;
	while (s[i] && (ft_strchr(LABEL_CHARS, s[i]) || (s[i] == LABEL_CHAR)))
	{
		if (s[i] == LABEL_CHAR)
			nb_2dots++;
		i++;
	}
	return ((nb_2dots == 1 && s[i - 1] == LABEL_CHAR) ? 1 : 0);
}

int		ft_check_label(char **tab, t_list **label, int *position)
{
	t_label		data;

	if (ft_check_label_word(tab[0]))
	{
		data.name = ft_strsub(tab[0], 0, ft_strlen(tab[0]) - 1);
		data.position = *position;
		if (label)
			ft_lstaddlast(label, ft_lstnew(&data, sizeof(t_label)));
		else
			*label = ft_lstnew(&data, sizeof(t_label));
		return (1);
	}
	return (0);
}
