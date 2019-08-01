/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_rooms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 05:19:13 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 05:33:12 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	pre_init(t_all *all, int *x, int *y)
{
	t_list	*room;

	*x = 1;
	*y = 0;
	room = all->rooms;
	ROOM->x = 0;
	ROOM->y = 0;
}

void		normalize_rooms(t_all *all)
{
	t_list	*room;
	int		x;
	int		y;

	pre_init(all, &x, &y);
	room = room->next;
	while (room)
	{
		while (y != x)
		{
			ROOM->x = x;
			ROOM->y = y++;
			if (!(room = room->next))
				return ;
		}
		while (x >= 0)
		{
			ROOM->x = x--;
			ROOM->y = y;
			if (!(room = room->next))
				return ;
		}
		x = y + 1;
		y = 0;
	}
}
