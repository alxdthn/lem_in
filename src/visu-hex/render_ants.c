/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 21:10:26 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/31 07:34:49 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	draw_ant(t_all *all, t_ant *ant)
{
	t_line_params	params;
	int				radius;

	all->mlx.ants.pixel_color = get_gradient(ant->start_point,
	ant->end_point, ant->cur_point);
	params.x1 = ant->x1;
	params.y1 = ant->y1;
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

static void	count_ant_params(t_all *all, t_ant *ant)
{
	ant->x1 = ((t_room *)ant->path->content)->x;
	ant->y1 = ((t_room *)ant->path->content)->y;
	if (ant->path->next)
	{
		ant->x2 = ((t_room *)ant->path->next->content)->x;
		ant->y2 = ((t_room *)ant->path->next->content)->y;
	}
	ant->delta_x = ABS(ant->x2 - ant->x1);
	ant->delta_y = ABS(ant->y2 - ant->y1);
	ant->dir_x = (ant->x1 < ant->x2) ? 1 : -1;
	ant->dir_y = (ant->y1 < ant->y2) ? 1 : -1;
	ant->speed_x = ant->delta_x / all->mlx.speed;
	ant->speed_y = ant->delta_y / all->mlx.speed;
	ant->is_counted = 1;
}

static void	moove_ant(t_all *all, t_ant *ant)
{
	if (ABS(ant->x1 - ant->x2) < 0.1)
		ant->x1 = ant->x2;
	else
		ant->x1 += ant->speed_x * ant->dir_x;
	if (ABS(ant->y1 - ant->y2) < 0.1)
		ant->y1 = ant->y2;
	else
		ant->y1 += ant->speed_y * ant->dir_y;
	ant->cur_point += ant->speed_x + ant->speed_y;
	if (ant->x1 == ant->x2 && ant->y1 == ant->y2)
	{
		ant->in_place = 1;
		if (((t_room *)ant->path->next->content)->type == END)
			all->mlx.ants_in_end++;
	}
}

static void	get_next_iteration(t_all *all)
{
	size_t	i;
	t_list	*tmp;
	t_ant	*ant;

	i = 0;
	while ((ant = all->iterations[all->mlx.cur_iter][i]))
	{
		draw_ant(all, ant);
		tmp = ant->path->next;
		free(ant->path);
		ant->path = tmp;
		ant->is_counted = 0;
		ant->in_place = 0;
		i++;
	}
	all->mlx.cur_iter++;
	render_info(all);
}

void		render_ants(t_all *all)
{
	size_t	j;
	t_ant	*ant;
	char	flag;

	j = 0;
	flag = 0;
	ft_memset(all->mlx.ants.data, 0xFF000000, sizeof(int) * all->mlx.ants.size);
	while (all->iterations[all->mlx.cur_iter][j])
	{
		ant = all->iterations[all->mlx.cur_iter][j++];
		if (ant->path && !ant->in_place)
		{
			if (!ant->is_counted)
				count_ant_params(all, ant);
			draw_ant(all, ant);
			moove_ant(all, ant);
			flag = 1;
		}
	}
	if (!flag)
		get_next_iteration(all);
}
