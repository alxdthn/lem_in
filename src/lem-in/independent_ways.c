/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   independent_ways.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 01:46:40 by skrystin          #+#    #+#             */
/*   Updated: 2019/07/31 17:46:06 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_independent_ways(t_all *all, t_room **room, int i)
{
	while (room && room[i])
	{
		if (room[i]->visit_early == '2' && i != 0 && i != all->room_count - 1)
		{
		//	ft_putstr(room[i]->name);
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
					// ft_printf("\nroom toopen 1 - %s, room toopen 2 room - %s; close first - %c, close second - %c\n",
					// ((t_door *)second->content)->room->name, ((t_door *)tmp->content)->room->name, ((t_door *)second->content)->is_close, ((t_door *)tmp->content)->is_close);
					((t_door *)second->content)->is_close = '\0';
					((t_door *)tmp->content)->is_close = '\0';
					((t_door *)second->content)->is_neccessary = '1';
					((t_door *)tmp->content)->is_neccessary = '1';
				}
				else
				{
				//	ft_printf("\nfirst room - %s, second room - %s; close first - %c, close second - %c\n",
				//	((t_door *)second->content)->room->name, ((t_door *)tmp->content)->room->name, ((t_door *)second->content)->is_close, ((t_door *)tmp->content)->is_close);
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
	t_ways	*tmp;
	t_ways	*next;

	tmp = all->ways;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->way);
		free(tmp);
		i = 0;
		tmp = next;
	}
//	free(all->ways);
}
