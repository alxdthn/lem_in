/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 18:26:49 by skrystin          #+#    #+#             */
/*   Updated: 2019/07/29 00:37:33 by skrystin         ###   ########.fr       */
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
}

void		ft_go_to_graph(t_que **q, t_all *all, int *nbr)
{
	t_que	*new;
	t_list	*doors;
	t_door	*tmp;

	new = 0;
	while (*q)
	{
		if ((*q)->room->visit == -1)
			(*q)->room->visit = *nbr;
		doors = (*q)->room->doors;
		while (doors)
		{
			tmp = doors->content;
			if (tmp->room->visit == -1 && !tmp->is_close)
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

int			ft_bfs(t_all *all, t_list *begin)
{
	t_que	*q;
	int		nbr;

	nbr = 0;
	q = 0;
	ft_push_back(all->mas_rom[0], &q, all);
	while (q && all->mas_rom[all->room_count - 1]->visit == -1)
		ft_go_to_graph(&q, all, &nbr);
//	ft_putnbr(all->mas_rom[all->room_count - 1]->visit);
	if (all->mas_rom[all->room_count - 1]->visit == -1)
	{
		ft_clean_index(all);
		return (0);
	}
	ft_create_ways(all, all->mas_rom[all->room_count - 1]->visit,
	all->room_count - 1);
	// nbr = 0;
	// while (all->mas_rom[nbr])
	// {
	// 	ft_putstr(all->mas_rom[nbr]->name);
	// 	ft_putstr(" - ");
	// 	ft_putnbr(all->mas_rom[nbr++]->visit);
	// 	ft_putchar('\n');
	// }
	ft_clean_index(all);
	return (1);
}
