/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ways.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:04:39 by skrystin          #+#    #+#             */
/*   Updated: 2019/07/31 02:43:39 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void        close_doors(t_all *all)
{
    t_ways  *tmp;
	t_door	*door;
	t_list	*rooms;
	int		i;
	
	tmp = all->ways;
	if (!tmp)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	i = 0;
	while (tmp->way[i + 1])
	{
		rooms = tmp->way[i]->doors;
		if (tmp->way[i]->visit_early == '1' && i != 0 && i != tmp->len)
		{
//			ft_printf("problem at- %s\n", tmp->way[i]->name);
			tmp->way[i]->visit_early = '2';
		}
		else if (i != 0 && i != tmp->len)
			tmp->way[i]->visit_early = '1';
		// ft_printf("visit early - %s\n", tmp->way[i]->name);
		while (rooms)
		{
			door = rooms->content;
			if (door->room == tmp->way[i + 1])
			{
				door->is_close = '1';
				break ;
			}
			rooms = rooms->next;
		}
		i++;
	}
}

void		delete_ants_from_path(t_ways *first, t_ways *second)
{
	while (first)
	{
		(first)->ants = 0;
		first = (first)->next;
	}
	while (second)
	{
		(second)->ants = 0;
		second = (second)->next;
	}
}

void        get_ways(t_all *all, t_list *begin)
{
	t_ways	*tmp;
	
    create_mas(all, all->rooms);
	while (bfs(all, all->rooms))
		close_doors(all);
	while (!is_independent_ways(all, all->mas_rom, 0))
	{
		clean_room_open_ways(all, all->mas_rom, 0, 0);
		all->tmp_dep_way = all->ways;
		// if (!(all->dependent_ways))
		// 	all->dependent_ways = all->ways;
		// else
			all->ways = 0;
		//	delete_ways(all, 0);		
		all->ways = 0;
		while (bfs(all, all->rooms))
			close_doors(all);
		if (!choose_ways(all, all->ant_count, all->ways, all->tmp_dep_way))
		{
			ft_putstr("Hi");
			delete_ants_from_path(all->ways, all->tmp_dep_way);
			all->ways = all->tmp_dep_way;
			break;
		}
		delete_ants_from_path(all->ways, all->tmp_dep_way);
		tmp = all->ways;
		all->ways = all->tmp_dep_way;
		all->tmp_dep_way = tmp;
		if (!(all->dependent_ways))
			all->dependent_ways = all->ways;
		else
			delete_ways(all, 0);
		all->ways = all->tmp_dep_way;
	}
	if (all->dependent_ways && is_independent_ways(all, all->mas_rom, 0))
		choose_ways(all, all->ant_count, all->ways, all->dependent_ways);
	else
		distribute_ants_to_ways(all, all->ways, all->ways, 0);
}
