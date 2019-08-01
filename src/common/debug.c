/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:11:50 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 18:16:54 by nalexand         ###   ########.fr       */
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

static void	print_rooms_list(t_list *room)
{
	while (room)
	{
		if (ROOM->type == START)
			ft_printf("%{blu}");
		else if (ROOM->type == END)
			ft_printf("%{red}");
		ft_printf("|%-25.*s|  %-4d|   %-4d|   %-4d|%d|%{eoc}",
		ROOM->name_len, ROOM->name, ROOM->way_nb,
		ROOM->x, ROOM->y, ROOM->normalized);
		if (ROOM->doors)
			print_doors_list(ROOM->doors);
		ft_putchar('\n');
		room = room->next;
	}
}

void		print(t_all *all)
{
	ft_printf("|___________name__________|_path_|___x___|___y___|\n");
	print_rooms_list(all->rooms);
	ft_printf("|_________________________|______|_______|_______|\n");
	ft_printf("ants: %d\n", all->ant_count);
}

void		print_ant_path(t_list *ant, int name)
{
	while (ant && ANT->name != name)
		ant = ant->next;
	print_rooms_list(ANT->path);
}

void		print_ants(t_all *all)
{
	t_list	*ant;

	ft_printf("\nANTS\n______________\n");
	ft_printf("_name_|_way_\n");
	ant = all->ants;
	while (ant)
	{
		ft_printf("%-6d| ", ANT->name);
		if (ANT->way)
		{
			print_way(ANT->way, 1);
			ft_printf("\n");
		}
		else
			ft_printf("%p\n", ANT->way);
		ant = ant->next;
	}
}
