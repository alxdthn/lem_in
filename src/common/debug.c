/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:11:50 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/21 18:30:32 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_doors_list(t_list *tmp)
{
	if (tmp->next)
		print_doors_list(tmp->next);
	ft_printf(" %s,", ((t_door *)tmp->content)->room->name);
}

static void	print_rooms_list(t_list *tmp)
{
	char	*name;
	int		x;
	int		y;

	if (tmp->next)
		print_rooms_list(tmp->next);
	name = ((t_room *)tmp->content)->name;
	x = ((t_room *)tmp->content)->x;
	y = ((t_room *)tmp->content)->y;
	if (((t_room *)tmp->content)->type == START)
		ft_printf("|%{gre}10s|%{gre}7d|%{gre}7d|", name, x, y);
	else if (((t_room *)tmp->content)->type == END)
		ft_printf("|%{yel}10s|%{yel}7d|%{yel}7d|", name, x, y);
	else
		ft_printf("|%10s|%7d|%7d|", name, x, y);
	print_doors_list(((t_room *)tmp->content)->doors);
	ft_putchar('\n');
}

void		print(t_all *all)
{
	ft_printf("|___name___|___x___|___y___|\n");
	print_rooms_list(all->rooms);
	ft_printf("|__________|_______|_______|\n");
	ft_printf("ants: %d\n", all->ants);
}
