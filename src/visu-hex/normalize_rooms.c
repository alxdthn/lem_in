/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_rooms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 05:19:13 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 09:32:47 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
/*
static void	normalizer(t_list *door, t_room *room, int y)
{
	int x;
	t_list	*head;

	x = 0;
	head = door;
	while (door)
	{
		if (DOOR->room != room && !DOOR->room->normalized)
		{
			DOOR->room->normalized++;
			DOOR->room->x = x++;
			DOOR->room->y = y;
			//normalizer(DOOR->room->doors, DOOR->room, y + 1);
		}
		door = door->next;
	}
}

void		normalize_rooms(t_all *all)
{
	t_list	*room;
	t_list	*door;
	int		x;
	int		y;

	x = 0;
	y = 0;
	all->start_room->x = 0;
	all->start_room->y = 0;
	all->start_room->normalized = 1;
	room = all->rooms;
	while (room)
	{
		ROOM->x = 0;
		ROOM->y = 0;
		room = room->next;
	}
	normalizer(all->start_room->doors, all->start_room, y + 1);
	t_list	*door;
	room = all->start_room-door;
	while (door)
	{

		normalizer(, ((t_door *)all->start_room->doors->content)->room, y + 2);
		door = door->next;
	}
	print(all);
}
*/

void		normalize_rooms(t_all *all)
{
	t_list	*room;

	room = all->rooms;
	while (room)
	{
		ROOM->x = 0;
		ROOM->y = 0;
		room = room->next;
	}
}
/*
void		normalize_rooms(t_all *all)
{
	t_list	*room;
	int		x;
	int		y;

	room = all->rooms;
	ROOM->x = 0;
	ROOM->y = 0;
	x = 1;
	y = 0;
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

*/