/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 05:21:11 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 08:18:11 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	count_ants_paths(t_all *all)
{
	t_list	*ant;
	t_list	*path;
	int		path_size;

	ant = all->ants;
	while (ant)
	{
		path = ANT->path;
		while (path)
		{
			if (path->next)
			{
				path_size = ABS(((t_room *)path->content)->x
				- ((t_room *)path->next->content)->x)
				+ ABS(((t_room *)path->content)->y
				- ((t_room *)path->next->content)->y);
				ANT->end_point += path_size;
				if (path_size < all->mlx.min_path_size
				|| !all->mlx.min_path_size)
					all->mlx.min_path_size = path_size;
			}
			path = path->next;
		}
		ant = ant->next;
	}
}

void	init_map(t_all *all)
{
	get_min_max(all);
	normalize(all);
	init_sizes(all);
	reset_crds(all);
	count_ants_paths(all);
	if ((all->mlx.room_radius = all->mlx.min_path_size / 3) < 4)
		all->mlx.room_radius = (all->ants) ? 4 : 50;
	if (all->mlx.room_radius > 50)
		all->mlx.room_radius = 50;
	if ((all->mlx.ant_radius = all->mlx.room_radius / 2) < 3)
		all->mlx.ant_radius = 3;
	if ((all->mlx.pixel_size = all->mlx.room_radius / 15) < 2)
		all->mlx.pixel_size = 2;
	all->mlx.speed = all->mlx.map_size / 10 + 20;
}
