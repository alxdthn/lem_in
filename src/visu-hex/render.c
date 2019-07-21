/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 20:10:20 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/21 22:57:05 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	put_logo(t_all *all)
{
	if (all->mlx.logo.ptr)
		mlx_put_image_to_window(all->mlx.ptr,
		all->mlx.win, all->mlx.logo.ptr, 10, 10);
}

static void	drawpixel(t_all *all, int x, int y)
{
	size_t	point;

	point = y * all->mlx.img.size_line + x;
	if (point > 0 && point < all->mlx.size)
		all->mlx.img.data[point] = 0xfc4242;
}

static void	print_circle(t_all *all, int R, int X1, int Y1)
{
   int x = 0;
   int y = R;
   int delta = 1 - 2 * R;
   int error = 0;
   while (y >= 0)
   {
		drawpixel(all, X1 + x, Y1 + y);
		drawpixel(all, X1 + x, Y1 - y);
		drawpixel(all, X1 - x, Y1 + y);
		drawpixel(all, X1 - x, Y1 - y);
		error = 2 * (delta + y) - 1;
       if ((delta < 0) && (error <= 0))
	   {
           delta += 2 * ++x + 1;
           continue ;
	   }
       if ((delta > 0) && (error > 0))
	   {
           delta -= 2 * --y + 1;
           continue ;
	   }
       delta += 2 * (++x - y--);
	}
}

void	bresenhem(t_all *all, int x1, int y1, int x2, int y2)
{
	int		error;
	int		error2;
	int		delta_x;
	int		delta_y;
	int		dir_x;
	int		dir_y;

	delta_x = ABS(x2 - x1);
	delta_y = ABS(y2 - y1);
	error = delta_x - delta_y;
	dir_x = x1 < x2 ? 1 : -1;
	dir_y = y1 < y2 ? 1 : -1;
	while (x1 != x2 || y1 != y2)
	{
		drawpixel(all, x1, y1);
		error2 = error * 2;
		if (error2 > -delta_y)
		{
			error -= delta_y;
			x1 += dir_x;
		}
		else if (error2 < delta_x)
		{
			error += delta_x;
			y1 += dir_y;
		}
	}
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

static void	print_lines(t_all *all, t_room *room, t_list *doors)
{
	while (doors)
	{
		if (!((t_door *)doors->content)->is_print)
		{
			bresenhem(all, room->x * 50, room->y * 50, ((t_door *)doors->content)->room->x * 50, ((t_door *)doors->content)->room->y * 50);
			get_door_by_room_name(all, ((t_door *)doors->content)->room, room->name)->is_print = 1;			
		}
		doors = doors->next;
	}
}

void		render(t_all *all)
{
	int i;
	t_list *tmp;

	i = 0;
	while (i < all->mlx.img.size_line * all->mlx.height - 1)
		all->mlx.img.data[i++] = 0xFFFFFF;
	tmp = all->rooms;
	while (tmp)
	{
		print_circle(all, 10, ((t_room *)tmp->content)->x * 50, ((t_room *)tmp->content)->y * 50);
		print_lines(all, (t_room *)tmp->content, ((t_room *)tmp->content)->doors);
		tmp = tmp->next;
	}
	mlx_put_image_to_window(all->mlx.ptr, all->mlx.win, all->mlx.img.ptr, 0, 0);
	put_logo(all);
}
