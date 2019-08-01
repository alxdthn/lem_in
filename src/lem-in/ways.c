/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 19:17:19 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/01 16:52:09 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_push_front_way(t_all *all, t_way *way, t_room *room, int len)
{
	if (!way)
		return ;
	if (!way->path)
	{
		if (!(way->path = (t_room **)malloc((sizeof(t_room *) * (len + 1)))))
			all->exit(all, ERROR, 2);
		way->path[len] = NULL;
	}
	way->path[room->visit] = room;
}

int			ft_is_close(t_room *start, t_room *finish)
{
	t_list	*door;

	door = start->doors;
	while (door)
	{
		if (DOOR->room == finish && DOOR->is_close)
			return (1);
		else if (DOOR->room == finish && !DOOR->is_close)
			return (0);
		door = door->next;
	}
	return (0);
}

void		create_way(t_all *all, int i, int end)
{
	t_way	new_way;
	t_list	*node;
	t_list	*door;

	new_way.len = all->mas_rom[end]->visit;
	new_way.path = NULL;
	new_way.ants = 0;
	new_way.nb = ++all->way_count;
	ft_push_front_way(all, &new_way, all->mas_rom[end], new_way.len + 1);
	while (i > 0)
	{
		door = new_way.path[i]->doors;
		while (DOOR->room->visit != i - 1 ||
		ft_is_close(DOOR->room, new_way.path[i]))
			door = door->next;
		ft_push_front_way(all, &new_way, DOOR->room, new_way.len);
		i--;
	}
	static int	s;

	ft_printf("new %d len %d\n", s++, new_way.len);
	if (!(node = ft_lstnew(&new_way, sizeof(t_way))))
		all->exit(all, ERROR, 2);
	ft_lstpushback(&all->ways, node);
}
