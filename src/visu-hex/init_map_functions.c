/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 05:24:30 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 05:27:46 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_min_max(t_all *all)
{
	t_list	*room;

	room = all->rooms;
	all->mlx.min_x = ROOM->x;
	all->mlx.min_y = ROOM->y;
	all->mlx.max_x = ROOM->x;
	all->mlx.max_y = ROOM->y;
	while (room)
	{
		if (ROOM->x < all->mlx.min_x)
			all->mlx.min_x = ROOM->x;
		if (ROOM->x > all->mlx.max_x)
			all->mlx.max_x = ROOM->x;
		if (ROOM->y < all->mlx.min_y)
			all->mlx.min_y = ROOM->y;
		if (ROOM->y > all->mlx.max_y)
			all->mlx.max_y = ROOM->y;
		room = room->next;
	}
}

int		pre_size(t_all *all)
{
	int		res;
	int		min_x;
	int		max_x;
	int		min_y;
	int		max_y;

	res = 1;
	min_x = all->mlx.min_x;
	max_x = all->mlx.max_x;
	min_y = all->mlx.min_y;
	max_y = all->mlx.max_y;
	while (max_x - min_x >= all->mlx.width && max_y - min_y >= all->mlx.height)
	{
		min_x = all->mlx.min_x / res;
		max_x = all->mlx.max_x / res;
		min_y = all->mlx.min_y / res;
		max_y = all->mlx.max_y / res;
		res++;
	}
	return (res);
}

void	normalize(t_all *all)
{
	t_list	*room;
	int		nb;
	int		size;

	size = pre_size(all);
	room = all->rooms;
	nb = 0;
	while (room)
	{
		ROOM->x -= all->mlx.min_x;
		ROOM->y -= all->mlx.min_y;
		ROOM->x /= size;
		ROOM->y /= size;
		ROOM->nb = nb++;
		room = room->next;
	}
	all->mlx.max_x -= all->mlx.min_x;
	all->mlx.max_y -= all->mlx.min_y;
	all->mlx.max_x /= size;
	all->mlx.max_y /= size;
	all->mlx.min_x = 0;
	all->mlx.min_y = 0;
}

void	init_sizes(t_all *all)
{
	int		x_size;
	int		y_size;
	int		min_max_x;
	int		min_max_y;

	if (!(min_max_x = all->mlx.max_x - all->mlx.min_x))
		min_max_x = 1;
	if (!(min_max_y = all->mlx.max_y - all->mlx.min_y))
		min_max_y = 1;
	x_size = (all->mlx.width - all->mlx.width / 5) / (min_max_x);
	y_size = (all->mlx.height - all->mlx.height / 5) / (min_max_y);
	if (!(all->mlx.map_size = (x_size > y_size) ? y_size : x_size))
		all->mlx.map_size = 1;
	if ((all->mlx.map_position_x = all->mlx.width / 2
	- (min_max_x * all->mlx.map_size) / 2) < 0)
		all->mlx.map_position_x = 0;
	if ((all->mlx.map_position_y = all->mlx.height / 2
	- ((min_max_y) * all->mlx.map_size) / 2) < 0)
		all->mlx.map_position_y = 0;
}

void	reset_crds(t_all *all)
{
	t_list	*room;

	room = all->rooms;
	while (room)
	{
		ROOM->x = ROOM->x * all->mlx.map_size + all->mlx.map_position_x;
		ROOM->y = ROOM->y * all->mlx.map_size + all->mlx.map_position_y;
		room = room->next;
	}
}
