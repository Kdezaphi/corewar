/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 10:12:16 by kdezaphi          #+#    #+#             */
/*   Updated: 2014/11/05 10:12:18 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_strclr(char *s)
{
	int		i;

	i = -1;
	if (s)
		while (s[++i] != '\0')
			s[i] = '\0';
}
