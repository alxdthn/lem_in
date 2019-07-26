/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 21:10:26 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/26 23:45:41 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void draw_ant(t_all *all, int x, int y)
{
	t_line_params	params;
	int				radius;

	params.x1 = x;
	params.y1 = y;
	radius = all->mlx.ant_radius;
	while (radius >= 0)
	{
		params.x2 = 0;
		params.y2 = radius;
		params.delta_x = 1 - 2 * radius;
		radius -= all->mlx.pixel_size;
		draw_circle(&all->mlx.ants, &params);
	}
}

static void	count_ant_params(t_ant *ant, int x2, int y2)
{
	ant->delta_x = ABS(x2 - ant->x);
	ant->delta_y = ABS(y2 - ant->y);
	ant->dir_x = (ant->x < x2) ? 1 : -1;
	ant->dir_y = (ant->y < y2) ? 1 : -1;
	ant->error = ant->delta_x - ant->delta_y;
	ant->is_counted = 1;
}

static void get_new_crds(t_all *all, t_ant *ant)
{
	if (ant->x == ((t_room *)ant->path->content)->x
	&& ant->y == ((t_room *)ant->path->content)->y)
		return ;
	ant->error2 = ant->error * 2;
	if (ant->error2 > -ant->delta_y)
	{
		ant->error -= ant->delta_y;
		ant->x += ant->dir_x * all->mlx.speed;
	}
	if (ant->error2 < ant->delta_x)
	{
		ant->error += ant->delta_x;
		ant->y += ant->dir_y * all->mlx.speed;
	}
}

static void	get_next_point(t_ant *ant)
{
	t_list	*tmp;

	tmp = ant->path->next;
	free(ant->path);
	ant->path = tmp;
	ant->is_counted = 0;
}

void	put_ants(t_all *all)
{
	size_t	j;
	int		x;
	int		y;
	t_ant	*ant;

	if (all->iterations[all->mlx.cur_iter])
	{
		j = 0;
		ft_memset(all->mlx.ants.data, 0xFF000000, sizeof(int) * all->mlx.ants.size);
		all->mlx.ants.pixel_color = ANT_COLOR;
		all->mlx.ants.pixel_size = all->mlx.pixel_size;
		while (all->iterations[all->mlx.cur_iter][j])
		{
			ant = all->iterations[all->mlx.cur_iter][j++];
			if (ant->path)// && ant->x != ((t_room *)ant->path->content)->x && ant->y != ((t_room *)ant->path->content)->y)
			{
				draw_ant(all, ant->x, ant->y);
				x = ((t_room *)ant->path->content)->x;
				y = ((t_room *)ant->path->content)->y;
				if (!ant->is_counted)
					count_ant_params(ant, x, y);
				get_new_crds(all, ant);
				//if (ant->x == x && ant->y == y)
			//		get_next_point(ant);
			}
		}
		//if (!flag)
		//	all->mlx.cur_iter++;
		mlx_put_image_to_window(all->mlx.ptr, all->mlx.win, all->mlx.ants.ptr, 0, 0);
	}
}
