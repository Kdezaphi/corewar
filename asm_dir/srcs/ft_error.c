/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rankierm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 10:01:33 by rankierm          #+#    #+#             */
/*   Updated: 2015/02/23 14:36:53 by rankierm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

/*
** Print on STD_ERR and [EXIT] (ASM_EXIT | ASM_NON_EXIT)
*/

void	ft_error(char *s, int line_position, char asm_exit)
{
	if (line_position)
		ft_printf_fd(2, "Syntax error on line %d: %s\n", line_position, s);
	else
		ft_printf_fd(2, "%s\n", s);
	if (asm_exit)
		exit(1);
}
