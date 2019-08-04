/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 18:26:49 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/02 16:11:05 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_go_to_g_two(t_all *all, t_list *doors, t_que **new, int flag)
{
	t_door *tmp;

	tmp = doors->content;
	while (doors->next && (!tmp->room->visit_early
	|| tmp->is_close) && tmp->room->visit_early != '2'
	&& (flag || tmp->room->visit_early != '1'))
	{
		doors = doors->next;
		tmp = doors->content;
	}
	if (tmp->room->visit == -1 && !tmp->is_close
	&& tmp->room->visit_early == '1')
		q_push_back(tmp->room, new, all);
}

void		ft_go_to_g_thr(t_all *all, t_que **q, t_list *doors, t_que **new)
{
	t_door	*tmp;

	tmp = doors->content;
	if (tmp->room->visit == -1 &&
	!tmp->is_close && tmp->room->visit_early != '2'
	&& (all->flag || tmp->room->visit_early != '1'))
		q_push_back(tmp->room, new, all);
	if (!(*q)->room->visit_early && tmp->room->visit_early
	&& tmp->room->visit == -1 && !tmp->is_close)
		tmp->room->go_away = '1';
}

void		ft_go_to_graph(t_que **q, t_all *all, int *nbr, int flag)
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
			ft_go_to_g_two(all, doors, &new, flag);
			del_first(q);
			continue;
		}
		while (doors)
		{
			ft_go_to_g_thr(all, q, doors, &new);
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

int			bfs(t_all *all, t_list *begin, int flag)
{
	t_que	*q;
	int		nbr;

	nbr = 0;
	all->flag = flag;
	q = 0;
	q_push_back(all->mas_rom[0], &q, all);
	while (q && all->mas_rom[all->room_count - 1]->visit == -1)
		ft_go_to_graph(&q, all, &nbr, flag);
	while (q)
		del_first(&q);
	if (nbr > 95)
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
