/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 21:07:21 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/26 21:08:27 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	draw_ways(t_all *all, t_room *room)
{
	t_line_params	params;
	t_list			*doors;

	all->mlx.map.pixel_color = WAY_COLOR;
	doors = room->doors;
	while (doors)
	{
		if (!((t_door *)doors->content)->is_print)
		{
			params.x1 = room->x;
			params.y1 = room->y;
			params.x2 = ((t_door *)doors->content)->room->x;
			params.y2 = ((t_door *)doors->content)->room->y;
			params.delta_x = ABS(params.x2 - params.x1);
			params.delta_y = ABS(params.y2 - params.y1);
			params.dir_x = (params.x1 < params.x2) ? 1 : -1;
			params.dir_y = (params.y1 < params.y2) ? 1 : -1;
			draw_line(&all->mlx.map, &params);
			find_door_by_room_nb(((t_door *)doors->content)->room,
			room->nb)->is_print = 1;
		}
		doors = doors->next;
	}
}

static void	draw_room(t_all *all, t_room *room)
{
	t_line_params	params;
	int				radius;

	all->mlx.map.pixel_color = ROOM_BORDER;
	params.x1 = room->x;
	params.y1 = room->y;
	params.x2 = 0;
	params.y2 = all->mlx.room_radius;
   	params.delta_x = 1 - 2 * all->mlx.room_radius;
	draw_circle(&all->mlx.map, &params);
	radius = all->mlx.room_radius - all->mlx.pixel_size + 1;
	while (--radius >= 0)
	{
		if (room->type == START)
			all->mlx.map.pixel_color = START_ROOM_COLOR;
		else if (room->type == END)
			all->mlx.map.pixel_color = END_ROOM_COLOR;
		else
			all->mlx.map.pixel_color = ROOM_FIL_COLOR;
		params.x2 = 0;
		params.y2 = radius;
	   	params.delta_x = 1 - 2 * radius;
		draw_circle(&all->mlx.map, &params);
	}
}

void	put_map(t_all *all)
{
	t_list *tmp;
	int 	i;

	i = 0;
	all->mlx.map.pixel_size = all->mlx.pixel_size;
	if (BACKGROUND_COLOR)
		while (i < all->mlx.map.size_line * all->mlx.height - 1)
			all->mlx.map.data[i++] = BACKGROUND_COLOR;
	tmp = all->rooms;
	while (tmp)
	{
		draw_ways(all, (t_room *)tmp->content);
		draw_room(all, (t_room *)tmp->content);
		tmp = tmp->next;
	}
	mlx_put_image_to_window(all->mlx.ptr, all->mlx.win, all->mlx.map.ptr, 0, 0);
}
