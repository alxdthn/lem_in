/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:11:50 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 04:59:55 by nalexand         ###   ########.fr       */
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
		ft_printf("|%-25.*s|  %-4d|   %-4d|   %-4d|%{eoc}",
		ROOM->name_len, ROOM->name, ROOM->way_nb, ROOM->x, ROOM->y);
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

void	print_ant_path(t_list *ant, int name)
{
	while (ant && ANT->name != name)
		ant = ant->next;
	print_rooms_list(ANT->path);
}

void	print_way(t_list *way, char print_path)
{
	int		room;

	ft_printf("path №%d (len %d, ants %d sum %d): ",
	WAY->nb, WAY->len, WAY->ants, (WAY->ants) ? WAY->len + WAY->ants : 0);
	room = 0;
	while (print_path && WAY->path[room])
	{
		ft_printf("%.*s", WAY->path[room]->name_len, WAY->path[room]->name);
		if (WAY->path[room + 1])
			ft_printf(" -> ");
		++room;
	}
	ft_putchar('\n');
}

void	print_ways(t_all *all, char print_path)
{
	t_list	*way;

	way = all->ways;
	while (way)
	{
		print_way(way, print_path);
		way = way->next;
	}
}

void	print_ants(t_all *all)
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

void	print_iterations(t_all *all)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (all->iterations[i])
	{
		j = 0;
		ft_printf("iteration: № %d\n", i);
		ft_printf("---------------\n");
		while (all->iterations[i][j])
		{
			ft_printf("name: L%d\n", all->iterations[i][j]->name);
			j++;
		}
		ft_printf("---------------\n");
		i++;
	}
}

void	print_info(t_all *all)
{
	ft_printf("min_path: %d\n", all->mlx.min_path_size);
	ft_printf("room: %d\n", all->mlx.room_radius);
	ft_printf("ant: %d\n", all->mlx.ant_radius);	
	ft_printf("pixel: %d\n", all->mlx.pixel_size);
	ft_printf("size: %d\n", all->mlx.map_size);	
}
