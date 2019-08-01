/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 18:26:49 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/01 15:04:28 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		create_mas(t_all *all, t_list *begin)
{
	int		i;

	i = all->room_count - 2;
	if (!(all->mas_rom = (t_room **)malloc(sizeof(t_room *)
	* (all->room_count + 1))))
		all->exit(all, ERROR, 2);
	all->mas_rom[all->room_count] = NULL;
	while (begin)
	{
		if (((t_room *)begin->content)->type == START)
		 	all->mas_rom[0] = (t_room *)begin->content;
		else if (((t_room *)begin->content)->type == END)
		 	all->mas_rom[all->room_count - 1] = (t_room *)begin->content;
		else
		{
			all->mas_rom[i] = begin->content;
			i--;
		}
		begin = begin->next;
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
		if ((*q)->room->go_away)
		{
			tmp = doors->content;
			while (doors->next && (!tmp->room->visit_early || tmp->is_close) && tmp->room->visit_early != '2')
			{
				doors = doors->next;
				tmp = doors->content;
			}
			if (tmp->room->visit == -1 && !tmp->is_close && tmp->room->visit_early == '1')
				q_push_back(tmp->room, &new, all);
			del_first(q);
			continue;
		}
		while (doors)
		{
			tmp = doors->content;
			if (tmp->room->visit == -1 && !tmp->is_close && tmp->room->visit_early != '2')
				q_push_back(tmp->room, &new, all);
			if (!(*q)->room->visit_early && tmp->room->visit_early && tmp->room->visit == -1 && !tmp->is_close)
				tmp->room->go_away = '1';
			doors = doors->next;
		}
		del_first(q);
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

int			bfs(t_all *all, t_list *begin)
{
	t_que	*q;
	int		nbr;

	nbr = 0;
	q = 0;
	q_push_back(all->mas_rom[0], &q, all);
	while (q && all->mas_rom[all->room_count - 1]->visit == -1)
		ft_go_to_graph(&q, all, &nbr);
	while (q)
		del_first(&q);
	if (nbr > 100)
		all->mas_rom[all->room_count - 1]->visit = -1;
	if (all->mas_rom[all->room_count - 1]->visit == -1)
	{
		ft_clean_index(all);
		return (0);
	}
	create_way(all, all->mas_rom[all->room_count - 1]->visit,
	all->room_count - 1);
	ft_clean_index(all);
	return (1);
}
