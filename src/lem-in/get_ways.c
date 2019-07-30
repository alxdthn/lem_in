/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:04:39 by skrystin          #+#    #+#             */
/*   Updated: 2019/07/30 01:47:36 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void        ft_close_doors(t_all *all)
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

void        get_ways(t_all *all, t_list *begin)
{
    ft_create_mas(all, all->rooms);
	while (ft_bfs(all, all->rooms))
		ft_close_doors(all);
//	ft_create_str(all, all->ways, all->ant_count, 1);
}
