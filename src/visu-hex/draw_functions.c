/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 20:17:43 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/22 23:04:40 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	draw_pixel(t_all *all, int x, int y)
{
	size_t	point;

	point = y * all->mlx.img.size_line + x;
	if (point > 0 && point < all->mlx.size && x >= 0)
		all->mlx.img.data[point] = all->mlx.color;
}

static void	draw_pixel_block(t_all* all, int x, int y)
{
	int		block_x;
	int		block_y;

	if (all->mlx.pixel_size == 1)
		draw_pixel(all, x, y);
	else
	{
		block_y = all->mlx.pixel_size;
		while (block_y)
		{
			block_x = all->mlx.pixel_size;
			while (block_x)
				draw_pixel(all, x + block_x--, y + block_y);
			--block_y;
		}
	}
}

void	draw_line(t_all *all, t_line_params *params)
{
	int		error;
	int		error2;

	error = params->delta_x - params->delta_y;
	while (params->x1 != params->x2 || params->y1 != params->y2)
	{
		draw_pixel_block(all, params->x1, params->y1);
		error2 = error * 2;
		if (error2 > -params->delta_y)
		{
			error -= params->delta_y;
			params->x1 += params->dir_x;
		}
		else if (error2 < params->delta_x)
		{
			error += params->delta_x;
			params->y1 += params->dir_y;
		}
	}
}

void	draw_circle(t_all *all, t_line_params *params)
{
	int error;

	error = 0;
	while (params->y2 >= 0)
   {
		draw_pixel_block(all, params->x1 + params->x2, params->y1 + params->y2);
		draw_pixel_block(all, params->x1 + params->x2, params->y1 - params->y2);
		draw_pixel_block(all, params->x1 - params->x2, params->y1 + params->y2);
		draw_pixel_block(all, params->x1 - params->x2, params->y1 - params->y2);
		error = 2 * (params->delta_x + params->y2) - 1;
       	if ((params->delta_x < 0) && (error <= 0))
		{
			params->delta_x += 2 * ++params->x2 + 1;
			continue ;
		}
		if ((params->delta_x > 0) && (error > 0))
		{
			params->delta_x -= 2 * --params->y2 + 1;
			continue ;
		}
		params->delta_x += 2 * (++params->x2 - params->y2--);
	}
}
