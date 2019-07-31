/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 18:26:49 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/01 00:10:11 by skrystin         ###   ########.fr       */
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
	while (begin)// && i != 0)
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
		// ft_printf("i - %d\n", i);
	}
//	ft_printf("start - %s, end - %s\n", all->mas_rom[0]->name, all->mas_rom[all->room_count - 1]->name);
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
		//	(*q)->room->go_away = '\0';
		//	ft_printf("go_aw - %s\n", (*q)->room->name);
			tmp = doors->content;
			while (doors->next && (!tmp->room->visit_early || tmp->is_close) && tmp->room->visit_early != '2')
			{
				doors = doors->next;
				tmp = doors->content;
				// if (tmp->room->name[0] == 'E')
				// 	break;
			}
			// ft_printf("room - %s\n", tmp->room->name);
			if (tmp->room->visit == -1 && !tmp->is_close && tmp->room->visit_early == '1')
				q_push_back(tmp->room, &new, all);
			del_first(q);
			continue;
		}
		while (doors)
		{
			tmp = doors->content;
		//	ft_printf("from - %s visit - %d, to - %s visit - %d\n", (*q)->room->name, (*q)->room->visit, tmp->room->name, tmp->room->visit);
			if (tmp->room->visit == -1 && !tmp->is_close && tmp->room->visit_early != '2' && (!flag || tmp->room->visit_early != '1'))
			{
			//	if (tmp->room->name[0] == 'D')
			//		ft_putstr(tmp->room->name);
				q_push_back(tmp->room, &new, all);
			}
			if (!(*q)->room->visit_early && tmp->room->visit_early && tmp->room->visit == -1 && !tmp->is_close && !flag)
			{
			//	ft_printf("from - %s visit - %d, to - %s visit - %d\n", (*q)->room->name, (*q)->room->visit, tmp->room->name, tmp->room->visit);
				tmp->room->go_away = '1';
			}
			if (tmp->is_neccessary && (*q)->room->visit != 0)
			{
			// //	ft_printf("from - %s to - %s\n", (*q)->room->name, tmp->room->name);
				tmp->is_neccessary = '\0';
				while (new && new->next)
					del_first(&new);
				if (new)
		//		q_push_back(tmp->room, &new, all);
				break;
			}
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
	q = 0;
	q_push_back(all->mas_rom[0], &q, all);
	while (q && all->mas_rom[all->room_count - 1]->visit == -1 && nbr < 92)
		ft_go_to_graph(&q, all, &nbr, flag);
	//ft_putnbr(all->mas_rom[all->room_count - 1]->type);
	if (all->mas_rom[all->room_count - 1]->visit == -1 || nbr == 92)
	{
//		ft_putstr(all->mas_rom[all->room_count - 1]->name);
		ft_clean_index(all);
		return (0);
	}
	create_ways(all, all->mas_rom[all->room_count - 1]->visit,
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
