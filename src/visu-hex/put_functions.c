/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 02:58:11 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/31 02:02:05 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	put_logo(t_all *all)
{
	if (all->mlx.logo.ptr)
		mlx_put_image_to_window(all->mlx.ptr,
		all->mlx.win, all->mlx.logo.ptr, 10, 10);
}

void	put_map(t_all *all)
{
	mlx_put_image_to_window(all->mlx.ptr,
	all->mlx.win, all->mlx.map.ptr, 0, 0);
}

void	put_ants(t_all *all)
{
	mlx_put_image_to_window(all->mlx.ptr,
	all->mlx.win, all->mlx.ants.ptr, 0, 0);
}

void	put_info(t_all *all)
{
	mlx_string_put(all->mlx.ptr, all->mlx.win,
	20, 75, INFO_COLOR, all->mlx.info_count_of_ants);
	mlx_string_put(all->mlx.ptr, all->mlx.win,
	20, 100, INFO_COLOR, all->mlx.info_iter);
	mlx_string_put(all->mlx.ptr, all->mlx.win,
	20, 125, INFO_COLOR, all->mlx.info_ant_in_end);
}

void	put_names(t_all *all)
{
	t_list	*room;

	room = all->rooms;
	while (room)
	{
		ROOM->name[ROOM->name_len] = '\0';
		mlx_string_put(all->mlx.ptr, all->mlx.win,
		ROOM->x - ROOM->name_len * 5,
		ROOM->y - 11, ROOM_NAME_COLOR, ROOM->name);
		ROOM->name[ROOM->name_len] = ' ';
		room = room->next;
	}
}
