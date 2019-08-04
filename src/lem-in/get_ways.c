/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ways.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:04:39 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/02 16:16:55 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		close_doors(t_all *all, int i, t_list *way)
{
	t_list	*door;
	t_list	*room;

	if (!way)
		return ;
	while (way->next)
		way = way->next;
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

void		one_step(t_all *all)
{
	((t_way *)all->ways->content)->ants = all->ant_count;
}

void		get_ways(t_all *all, t_list *begin, int i)
{
	create_mas(all, all->rooms);
	if (!bfs(all, all->rooms, i))
		all->exit(all, "Error: no path", 2);
	close_doors(all, 0, all->ways);
	if (((t_way *)all->ways->content)->len == 1)
		return (one_step(all));
	while (bfs(all, all->rooms, i))
		close_doors(all, 0, all->ways);
	while (!is_independent_ways(all, all->mas_rom, 0) && i--)
	{
		clean_room_open_ways(all, all->mas_rom, 0, 0);
		if (!(all->dependent_ways))
			all->dependent_ways = all->ways;
		else
			ft_lstdel(&all->ways, clear_way);
		all->ways = NULL;
		while (bfs(all, all->rooms, i))
			close_doors(all, 0, all->ways);
	}
	if (all->dependent_ways)
		choose_ways(all, all->ant_count, all->ways, all->dependent_ways);
	else
		distribute_ants_to_ways(all, all->ways, all->ways, 0);
}
