/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:35:53 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/27 20:42:00 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_iterations(t_all *all)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (all->iterations[i])
	{
		j = 0;
		ft_printf("iteration: № %d\n", i);
		ft_printf("---------------\n");
		while (all->iterations[i][j])
		{
			ft_printf("name: %d\n", all->iterations[i][j]->name);
			ft_printf("x1: %d\n", all->iterations[i][j]->x1);
			ft_printf("y1: %d\n", all->iterations[i][j]->y1);
			j++;
		}
		ft_printf("---------------\n");
		i++;
	}
}

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

static void	normalize_by_min(t_all *all)
{
	t_list	*tmp;
	int		nb;

	tmp = all->rooms;
	nb = 0;
	while (tmp)
	{
		((t_room *)tmp->content)->x -= all->mlx.min_x;
		((t_room *)tmp->content)->y -= all->mlx.min_y;
		((t_room *)tmp->content)->nb = nb++;
		tmp = tmp->next;
	}
}

static void	reset_crds(t_all *all)
{
	t_list	*tmp;

	tmp = all->rooms;
	while (tmp)
	{
		((t_room *)tmp->content)->x = ((t_room *)tmp->content)->x * all->mlx.map_size + all->mlx.map_position_x;
		((t_room *)tmp->content)->y = ((t_room *)tmp->content)->y * all->mlx.map_size + all->mlx.map_position_y;
		if (((t_room *)tmp->content)->type == START)
			all->mlx.start_room = (t_room *)tmp->content;
		tmp = tmp->next;
	}
}

static void	init_map(t_all *all)
{
	int		x_size;
	int		y_size;

	get_min_max(all);
	normalize_by_min(all);
	x_size = (all->mlx.width - all->mlx.width / 5) / (all->mlx.max_x - all->mlx.min_x);
	y_size = (all->mlx.height - all->mlx.height / 5) / (all->mlx.max_y - all->mlx.min_y);
	all->mlx.map_size = (x_size > y_size) ? y_size : x_size;
	all->mlx.room_radius = 50;
	all->mlx.ant_radius = 20;
	all->mlx.map_position_x = all->mlx.width / 2 - ((all->mlx.max_x - all->mlx.min_x) * all->mlx.map_size) / 2;
	all->mlx.map_position_y = all->mlx.height / 2 - ((all->mlx.max_y - all->mlx.min_y) * all->mlx.map_size) / 2;
	all->mlx.pixel_size = 5;
	all->mlx.speed = 80;
	reset_crds(all);
}

int		main(void)
{
	t_all	all;

	ft_bzero(&all, sizeof(t_all));
	all.prog = VISU_HEX;
	all.exit = &visu_hex_clear_exit;
	visualisation_init(&all);
	parce_input(&all);
	init_map(&all);
	parce_ants(&all);
	render_map(&all);
	render_info(&all);
	put_map(&all);
	put_names(&all);
	put_logo(&all);
	all.mlx.ants.pixel_color = ANT_COLOR;
	all.mlx.ants.pixel_size = all.mlx.pixel_size;
	mlx_loop_hook(all.mlx.ptr, loop_hook, &all);
	mlx_loop(all.mlx.ptr);
	return (0);
}
