/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 20:10:20 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/25 21:05:15 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	put_logo(t_all *all)
{
	if (all->mlx.logo.ptr)
		mlx_put_image_to_window(all->mlx.ptr,
		all->mlx.win, all->mlx.logo.ptr, 10, 10);
}

static t_door	*get_door_by_room_name(t_all *all, t_room *room, char *name)
{
	t_list	*tmp;

	tmp = room->doors;
	while (tmp)
	{
		if (ft_strequ(((t_door *)tmp->content)->room->name, name))
			return ((t_door *)tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	draw_ways(t_all *all, t_room *room)
{
	t_line_params	params;
	t_list			*doors;

	all->mlx.color = WAY_COLOR;
	doors = room->doors;
	while (doors)
	{
		if (!((t_door *)doors->content)->is_print)
		{
			params.x1 = room->x * all->mlx.map_size + all->mlx.map_position_x;
			params.y1 = room->y * all->mlx.map_size + all->mlx.map_position_y;
			params.x2 = ((t_door *)doors->content)->room->x * all->mlx.map_size + all->mlx.map_position_x;
			params.y2 = ((t_door *)doors->content)->room->y * all->mlx.map_size + all->mlx.map_position_y;
			params.delta_x = ABS(params.x2 - params.x1);
			params.delta_y = ABS(params.y2 - params.y1);
			params.dir_x = (params.x1 < params.x2) ? 1 : -1;
			params.dir_y = (params.y1 < params.y2) ? 1 : -1;
			draw_line(all, &params);
			get_door_by_room_name(all, ((t_door *)doors->content)->room,
			room->name)->is_print = 1;
		}
		doors = doors->next;
	}
}

static void	draw_room(t_all *all, t_room *room)
{
	t_line_params	params;
	int				radius;

	all->mlx.color = ROOM_BORDER;
	params.x1 = room->x * all->mlx.map_size + all->mlx.map_position_x;
	params.y1 = room->y * all->mlx.map_size + all->mlx.map_position_y;
	params.x2 = 0;
	params.y2 = all->mlx.radius;
   	params.delta_x = 1 - 2 * all->mlx.radius;
	draw_circle(all, &params);
	radius = all->mlx.radius - all->mlx.pixel_size + 1;
	while (--radius >= 0)
	{
		if (room->type == START)
			all->mlx.color = START_ROOM_COLOR;
		else if (room->type == END)
			all->mlx.color = END_ROOM_COLOR;
		else
			all->mlx.color = ROOM_FIL_COLOR;
		params.x2 = 0;
		params.y2 = radius;
	   	params.delta_x = 1 - 2 * radius;
		draw_circle(all, &params);
	}
}

void		render(t_all *all)
{
	t_list *tmp;
	int 	i;
	int		pixel_size;

	i = 0;
	if (BACKGROUND_COLOR)
		while (i < all->mlx.img.size_line * all->mlx.height - 1)
			all->mlx.img.data[i++] = BACKGROUND_COLOR;
	tmp = all->rooms;
	while (tmp)
	{
		draw_ways(all, (t_room *)tmp->content);
		draw_room(all, (t_room *)tmp->content);
		tmp = tmp->next;
	}
	mlx_put_image_to_window(all->mlx.ptr, all->mlx.win, all->mlx.img.ptr, 0, 0);
	put_logo(all);
}
