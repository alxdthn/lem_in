/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:35:53 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/31 07:44:07 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	get_min_max(t_all *all)
{
	t_list	*tmp;

	tmp = all->rooms;
	all->mlx.min_x = ((t_room *)tmp->content)->x;
	all->mlx.min_y = ((t_room *)tmp->content)->y;
	all->mlx.max_x = ((t_room *)tmp->content)->x;
	all->mlx.max_y = ((t_room *)tmp->content)->y;
	while (tmp)
	{
		if (((t_room *)tmp->content)->x < all->mlx.min_x)
			all->mlx.min_x = ((t_room *)tmp->content)->x;
		if (((t_room *)tmp->content)->x > all->mlx.max_x)
			all->mlx.max_x = ((t_room *)tmp->content)->x;
		if (((t_room *)tmp->content)->y < all->mlx.min_y)
			all->mlx.min_y = ((t_room *)tmp->content)->y;
		if (((t_room *)tmp->content)->y > all->mlx.max_y)
			all->mlx.max_y = ((t_room *)tmp->content)->y;
		tmp = tmp->next;
	}
}

static int	pre_size(t_all *all)
{
	int		res;
	int		min_x;
	int		max_x;
	int		min_y;
	int		max_y;

	res = 1;
	min_x = all->mlx.min_x;
	max_x = all->mlx.max_x;
	min_y = all->mlx.min_y;
	max_y = all->mlx.max_y;
	while (max_x - min_x >= all->mlx.width && max_y - min_y >= all->mlx.height)
	{
		min_x = all->mlx.min_x / res;
		max_x = all->mlx.max_x / res;
		min_y = all->mlx.min_y / res;
		max_y = all->mlx.max_y / res;
		res++;
	}
	return (res);
}

static void	normalize(t_all *all)
{
	t_list	*tmp;
	int		nb;
	int		size;

	size = pre_size(all);
	tmp = all->rooms;
	nb = 0;
	while (tmp)
	{
		((t_room *)tmp->content)->x -= all->mlx.min_x;
		((t_room *)tmp->content)->y -= all->mlx.min_y;
		((t_room *)tmp->content)->x /= size;
		((t_room *)tmp->content)->y /= size;
		((t_room *)tmp->content)->nb = nb++;
		tmp = tmp->next;
	}
	all->mlx.max_x -= all->mlx.min_x;
	all->mlx.max_y -= all->mlx.min_y;
	all->mlx.max_x /= size;
	all->mlx.max_y /= size;
	all->mlx.min_x = 0;
	all->mlx.min_y = 0;
}

static void	reset_crds(t_all *all)
{
	t_list	*tmp;

	tmp = all->rooms;
	while (tmp)
	{
		((t_room *)tmp->content)->x = ((t_room *)tmp->content)->x
		* all->mlx.map_size + all->mlx.map_position_x;
		((t_room *)tmp->content)->y = ((t_room *)tmp->content)->y
		* all->mlx.map_size + all->mlx.map_position_y;
		tmp = tmp->next;
	}
}

static void	init_sizes(t_all *all)
{
	int		x_size;
	int		y_size;
	int		min_max_x;
	int		min_max_y;

	if (!(min_max_x = all->mlx.max_x - all->mlx.min_x))
		min_max_x = 1;
	if (!(min_max_y = all->mlx.max_y - all->mlx.min_y))
		min_max_y = 1;
	x_size = (all->mlx.width - all->mlx.width / 5) / (min_max_x);
	y_size = (all->mlx.height - all->mlx.height / 5) / (min_max_y);
	if (!(all->mlx.map_size = (x_size > y_size) ? y_size : x_size))
		all->mlx.map_size = 1;
	if ((all->mlx.map_position_x = all->mlx.width / 2
	- (min_max_x * all->mlx.map_size) / 2) < 0)
		all->mlx.map_position_x = 0;
	if ((all->mlx.map_position_y = all->mlx.height / 2
	- ((min_max_y) * all->mlx.map_size) / 2) < 0)
		all->mlx.map_position_y = 0;
}


static void	count_ants_paths(t_all *all)
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
				if (path_size < all->mlx.min_path_size || !all->mlx.min_path_size)
					all->mlx.min_path_size = path_size;
			}
			path = path->next;
		}
		ant = ant->next;
	}
}

static void	init_map(t_all *all)
{
	visualisation_init(all);
	get_min_max(all);
	normalize(all);
	init_sizes(all);
	reset_crds(all);
	count_ants_paths(all);
	ft_printf("%min_path: %d\n", all->mlx.min_path_size);
	if ((all->mlx.room_radius = all->mlx.min_path_size / 3) < 4)
		all->mlx.room_radius = 4;
	if (all->mlx.room_radius > 50)
		all->mlx.room_radius = 50;
	ft_printf("%room: %d\n", all->mlx.room_radius);
	if ((all->mlx.ant_radius = all->mlx.room_radius / 2) < 3)
		all->mlx.ant_radius = 3;
	ft_printf("ant: %d\n", all->mlx.ant_radius);	
	if ((all->mlx.pixel_size = all->mlx.room_radius / 15) < 2)
		all->mlx.pixel_size = 2;
	ft_printf("pixel: %d\n", all->mlx.pixel_size);
	ft_printf("size: %d\n", all->mlx.map_size);	
	all->mlx.speed = all->mlx.map_size / 3 + 20;
}

int			main(void)
{
	t_all	all;

	ft_bzero(&all, sizeof(t_all));
	all.prog = VISU_HEX;
	all.exit = &visu_hex_clear_exit;
	parce_input(&all);
	parce_ants(&all);
	init_map(&all);
	render_map(&all);
	render_info(&all);
	put_map(&all);
	put_logo(&all);
	put_info(&all);
	all.mlx.ants.pixel_size = all.mlx.pixel_size;
	mlx_loop_hook(all.mlx.ptr, loop_hook, &all);
	mlx_loop(all.mlx.ptr);
	return (0);
}
