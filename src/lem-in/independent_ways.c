/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   independent_ways.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 01:46:40 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/01 15:04:54 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_independent_ways(t_all *all, t_room **room, int i)
{
	while (room && room[i])
	{
		if (room[i]->visit_early == '2' && i != 0 && i != all->room_count - 1)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	clean_room_open_ways(t_all *all, t_room **room, t_list *second, int i)
{
	t_list	*tmp;

	while (room && room[i])
	{
		tmp = room[i]->doors;
		while (tmp)
		{
			if (((t_door *)tmp->content)->is_close)
			{
				second = ((t_door *)tmp->content)->room->doors;
				while (((t_door *)second->content)->room != room[i])
					second = second->next;
				if (!((t_door *)second->content)->is_close)
				{
					((t_door *)second->content)->is_close = '\0';
					((t_door *)tmp->content)->is_close = '\0';
				}
			}
			tmp = tmp->next;
		}
		room[i]->go_away = '\0';
		room[i]->visit_early = '\0';
		room[i]->visit = -1;
		i++;
	}
}

void	delete_ways(t_all *all, int i)
{
	t_list	*way;
	t_list	*next;

	way = all->ways;
	while (way)
	{
		next = way->next;
		free(WAY->path);
		free(way);
		i = 0;
		way = next;
	}
}
