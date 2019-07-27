/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:11:50 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/27 23:38:36 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_doors_list(t_list *tmp)
{
	if (tmp->next)
		print_doors_list(tmp->next);
	ft_printf(" %.*s,", ((t_door *)tmp->content)->room->name_len,
	((t_door *)tmp->content)->room->name);
}

static void	print_rooms_list(t_list *tmp)
{
	size_t	name_len;
	char	*name;
	int		x;
	int		y;

	if (tmp->next)
		print_rooms_list(tmp->next);
	name_len = ((t_room *)tmp->content)->name_len;
	name = ((t_room *)tmp->content)->name;
	x = ((t_room *)tmp->content)->x;
	y = ((t_room *)tmp->content)->y;
	if (((t_room *)tmp->content)->type == START)
		ft_printf("|%{blu}10.*s|%{blu}7d|%{blu}7d|", name_len, name, x, y);
	else if (((t_room *)tmp->content)->type == END)
		ft_printf("|%{red}10.*s|%{red}7d|%{red}7d|", name_len, name, x, y);
	else
		ft_printf("|%10.*s|%7d|%7d|", name_len, name, x, y);
	print_doors_list(((t_room *)tmp->content)->doors);
	ft_putchar('\n');
}

void	print_ants_list(t_list *ants)
{
	while (ants)
	{
		ft_printf("name: %d x: %d y: %d\n",
		((t_ant *)ants->content)->name,
		((t_ant *)ants->content)->x1,
		((t_ant *)ants->content)->y1);
		ants = ants->next;
	}
}

void		print(t_all *all)
{
	ft_printf("|___name___|___x___|___y___|\n");
	print_rooms_list(all->rooms);
	ft_printf("|__________|_______|_______|\n");
	ft_printf("ants: %d\n", all->ant_count);
}

void	print_ant_path(t_list *ants, int name)
{
	while (ants && ((t_ant *)ants->content)->name != name)
		ants = ants->next;
	print_rooms_list(((t_ant *)ants->content)->path);
}
