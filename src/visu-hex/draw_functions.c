/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 20:17:43 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/27 20:19:44 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	draw_pixel(t_img *img, int x, int y)
{
	size_t	point;

	point = y * img->size_line + x;
	if (point > 0 && point < img->size && x >= 0)
		img->data[point] = img->pixel_color;
}

void	draw_pixel_circle(t_img *img, t_line_params *params)
{
	int error;

	error = 0;
	while (params->y2 >= 0)
	{
		draw_pixel(img, params->x1 + params->x2, params->y1 + params->y2);
		draw_pixel(img, params->x1 + params->x2, params->y1 - params->y2);
		draw_pixel(img, params->x1 - params->x2, params->y1 + params->y2);
		draw_pixel(img, params->x1 - params->x2, params->y1 - params->y2);
		error = 2 * (params->delta_x + params->y2);
       	if ((params->delta_x < 0) && (error <= 0))
			params->delta_x += 2 * ++params->x2;
		else if ((params->delta_x > 0) && (error > 0))
			params->delta_x -= 2 * --params->y2;
		else
			params->delta_x += 2 * (++params->x2 - --params->y2);
	}
}

void	draw_point(t_img *img, int x, int y)
{
	t_line_params	params;
	int 			radius;

	if (img->pixel_size == 1)
		draw_pixel(img, x, y);
	else
	{
		radius = img->pixel_size;
		while (--radius >= 0)
		{
			params.x1 = x;
			params.y1 = y;
			params.x2 = 0;
			params.y2 = radius;
			params.delta_x = 1 - 2 * radius;
			draw_pixel_circle(img, &params);
		}
	}
}

void	draw_line(t_img *img, t_line_params *params)
{
	int		error;
	int		error2;

	error = params->delta_x - params->delta_y;
	while (params->x1 != params->x2 || params->y1 != params->y2)
	{
		draw_point(img, params->x1, params->y1);
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

void	draw_circle(t_img *img, t_line_params *params)
{
	int error;

	error = 0;
	while (params->y2 >= 0)
	{
		draw_point(img, params->x1 + params->x2, params->y1 + params->y2);
		draw_point(img, params->x1 + params->x2, params->y1 - params->y2);
		draw_point(img, params->x1 - params->x2, params->y1 + params->y2);
		draw_point(img, params->x1 - params->x2, params->y1 - params->y2);
		error = 2 * (params->delta_x + params->y2);
       	if ((params->delta_x < 0) && (error <= 0))
			params->delta_x += 2 * ++params->x2;
		else if ((params->delta_x > 0) && (error > 0))
			params->delta_x -= 2 * --params->y2;
		else
			params->delta_x += 2 * (++params->x2 - --params->y2);
	}
}
