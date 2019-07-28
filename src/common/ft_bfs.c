/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 18:26:49 by skrystin          #+#    #+#             */
/*   Updated: 2019/07/28 17:39:23 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_create_mas(t_all *all, t_list *begin)
{
	int		i;

	all->room_count = ft_lstcount(all->rooms);
	i = all->room_count - 2;
	if (!(all->mas_rom = (t_room **)malloc(sizeof(t_room *)
	* (all->room_count + 1))))
		all->exit(all, ERROR, 2);
	all->mas_rom[all->room_count] = 0;
	while (begin)
	{
		all->mas_rom[i] = begin->content;
		all->mas_rom[i]->visit = -1;
		begin = begin->next;
		if (all->mas_rom[i]->type == START)
			all->mas_rom[0] = all->mas_rom[i];
		else if (all->mas_rom[i]->type == END)
			all->mas_rom[all->room_count - 1] = all->mas_rom[i];
		else
			i--;
	}
	//  ft_putnbr(all->mas_rom[0]->visit);
	//  ft_putchar('\n');
}

void		ft_go_to_graph(t_que **q, t_all *all, int *nbr)
{
	t_que	*new;
	t_list	*doors;
	t_door	*tmp;

	new = 0;
	while (*q)
	{
		(*q)->room->visit = *nbr;
		doors = (*q)->room->doors;
		while (doors)
		{
			tmp = doors->content;
			if (tmp->room->visit == -1)
				ft_push_back(tmp->room, &new, all);
			doors = doors->next;
		}
		ft_del_first(q);
	}
	*nbr += 1;
	*q = new;
}

void		ft_clean_index(t_all *all)
{
	int		nbr;

	nbr = 0;
	while (all->mas_rom[nbr])
		all->mas_rom[nbr++]->visit = -1;
}

void		ft_create_ways(t_all *all, int i, int end)
{
	t_ways	*new;
	t_list	*tmp;
	t_door	*door;

	if (!(new = (t_ways *)malloc(sizeof(t_ways))))
		all->exit(all, ERROR, 2);
	new->len = all->mas_rom[end]->visit;
	new->next = 0;
	new->way = ft_push_front_way(all->mas_rom[end]);
	while (i > 0)
	{
		tmp = new->way[0]->doors;
		door = tmp->content;
		while (door->room->visit != i - 1)
		{
			tmp = tmp->next;
			door = tmp->content;
		}
		new->way = ft_push_front_way(door->room);
		i--;
	}
	ft_add_way(all, new);
}

void		ft_bfs(t_all *all, t_list *begin)
{
	t_que	*q;
	int		nbr;

	nbr = 0;
	q = 0;
	ft_push_back(all->mas_rom[0], &q, all);
	while (q)
		ft_go_to_graph(&q, all, &nbr);
	ft_create_ways(all, all->mas_rom[all->room_count - 1]->visit,
	all->room_count - 1);
	nbr = 0;
	while (all->mas_rom[nbr])
	{
		ft_putstr(all->mas_rom[nbr]->name);
		ft_putstr(" - ");
		ft_putnbr(all->mas_rom[nbr++]->visit);
		ft_putchar('\n');
	}
	ft_clean_index(all);
}
