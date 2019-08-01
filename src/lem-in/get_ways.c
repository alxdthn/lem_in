/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ways.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:04:39 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/01 15:00:32 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		close_doors(t_all *all)
{
    t_list	*way;
	t_list	*door;
	t_list	*room;
	int		i;
	
	way = all->ways;
	if (!way)
		return ;
	while (way->next)
		way = way->next;
	i = 0;
	while (WAY->path[i + 1])
	{
		if (WAY->path[i]->visit_early == '1' && i != 0 && i != WAY->len)
			WAY->path[i]->visit_early = '2';
		else if (i != 0 && i != WAY->len)
			WAY->path[i]->visit_early = '1';
		door = WAY->path[i]->doors;
		while (door)
		{
			if (DOOR->room == WAY->path[i + 1])
			{
				DOOR->is_close = '1';
				break ;
			}
			door = door->next;
		}
		i++;
	}
}

void        get_ways(t_all *all, t_list *begin, int i)
{
    create_mas(all, all->rooms);
	if (!bfs(all, all->rooms))
		all->exit(all, ERROR, 2);
	close_doors(all);
	// if (((t_way *)all->ways->content)->len == 2)
	// 	one_step(all);
	while (bfs(all, all->rooms))
		close_doors(all);
	while (!is_independent_ways(all, all->mas_rom, 0) && i--)
	{
		clean_room_open_ways(all, all->mas_rom, 0, 0);
		if (!(all->dependent_ways))
			all->dependent_ways = all->ways;
		else
			delete_ways(all, 0);		
		all->ways = 0;
		while (bfs(all, all->rooms))
			close_doors(all);
	}
	if (all->dependent_ways)
		choose_ways(all, all->ant_count, all->ways, all->dependent_ways);
	else
		distribute_ants_to_ways(all, all->ways, all->ways, 0);
}
