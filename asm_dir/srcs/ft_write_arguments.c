/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiraud- <mgiraud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 16:49:02 by atamano           #+#    #+#             */
/*   Updated: 2015/03/10 10:18:15 by mgiraud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

static void		ft_write_registre(int fd, char *str)
{
	int		i;

	str++;
	i = ft_atoi(str);
	if (i > REG_NUMBER)
		ft_error("reg number too big", 0, ASM_EXIT);
	ft_printf_fd(fd, "%c", (char)i);
}

static void		ft_write_label(int fd, char *str, t_list *list, t_list *label)
{
	short	pos;
	int		taille;
	int		size;

	size = ((t_line *)list->content)->size_from_begin;
	taille = (str[0] == DIRECT_CHAR ?
		ft_get_label_size(((t_line *)list->content)->opcode) : 2);
	if (str[0] == DIRECT_CHAR)
		str++;
	str++;
	while (label)
	{
		if (!ft_strcmp(((t_label *)label->content)->name, str))
			break ;
		label = label->next;
	}
	if (!label)
		ft_error("label not found", 0, ASM_EXIT);
	if (taille == 2)
		ft_write_oct(fd, ((t_label *)label->content)->position - size);
	else
	{
		pos = rev_int(((t_label *)label->content)->position - size);
		ft_write_int(fd, pos);
	}
}

static void		ft_write_direct(int fd, char *str, char *opcode)
{
	int	i;
	int	size;

	str++;
	size = ft_get_label_size(opcode);
	i = ft_atoi(str);
	if (size == 2)
		ft_write_oct(fd, i);
	else if (size == 4)
	{
		i = rev_int(i);
		write(fd, &i, 4);
	}
	else
		ft_error("no direct argument with this command", 0, ASM_EXIT);
}

static void		ft_write_indirect(int fd, char *str)
{
	int	i;

	if (str[0] != LABEL_CHAR)
	{
		i = ft_atoi(str);
		ft_write_oct(fd, i);
	}
}

void			ft_write_arguments(int fd, t_list *list, t_list *label)
{
	int		i;
	char	**args;

	args = ((t_line *)list->content)->args;
	i = -1;
	while (args[++i])
	{
		if (args[i][0] == 'r' && ft_isdigit(args[i][1]))
			ft_write_registre(fd, args[i]);
		else if ((args[i][0] == DIRECT_CHAR && args[i][1] == LABEL_CHAR)
			|| args[i][0] == LABEL_CHAR)
			ft_write_label(fd, args[i], list, label);
		else if (args[i][0] == DIRECT_CHAR)
			ft_write_direct(fd, args[i], ((t_line *)list->content)->opcode);
		else
			ft_write_indirect(fd, args[i]);
	}
}
