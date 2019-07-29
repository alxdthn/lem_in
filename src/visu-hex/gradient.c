/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 06:32:20 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/29 06:33:01 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

double	percentage(double start, double end, double cur)
{
	double	placement;
	double	distance;

	placement = cur - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

void	get_light(int *value, int start, int end, double percent)
{
	*value = (int)((1 - percent) * start + percent * end);
}

int		get_gradient(double start, double end, double cur)
{
	double	percent;
	int		red;
	int		green;
	int		blue;

	if (start >= end)
		return (END_ROOM_COLOR);
	percent = percentage(start, end, cur);
	get_light(&red, (START_ROOM_COLOR >> 16) & 0xFF,
	(END_ROOM_COLOR >> 16) & 0xFF, percent);
	get_light(&green, (START_ROOM_COLOR >> 8) & 0xFF,
	(END_ROOM_COLOR >> 8) & 0xFF, percent);
	get_light(&blue, START_ROOM_COLOR & 0xFF,
	END_ROOM_COLOR & 0xFF, percent);
	return ((red << 16) | (green << 8) | blue);
}
