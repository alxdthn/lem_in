/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:35:53 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 06:22:46 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char		*get_line(t_list *lines, int line_number)
{
	while (line_number--)
		lines = lines->next;
	return (lines->content);
}

static void	visu_part(t_all *all)
{
	if (!all->mlx.flags.no_visu)
	{
		if (all->mlx.flags.normalize_map)
			normalize_rooms(all);
		init_map(all);
		render_map(all);
		render_info(all);
		put_map(all);
		put_logo(all);
		put_info(all);
		all->mlx.ants.pixel_size = all->mlx.pixel_size;
		if (all->mlx.flags.print_info)
			print_info(all);
		if (all->iterations && all->mlx.flags.print_iterations)
			print_iterations(all);
		mlx_loop_hook(all->mlx.ptr, loop_hook, all);
		mlx_loop(all->mlx.ptr);
	}
}

static void	print_part(t_all *all)
{
	if (all->mlx.flags.print_err || all->mlx.flags.print_way_info
	|| all->mlx.flags.print_way_info_path)
	{
		validate_iterations(all);
		validate_ways(all);
	}
	if (all->mlx.flags.print_rooms)
		print(all);
	if (all->mlx.flags.print_way_info_path)
		print_ways(all, 1);
	if (all->mlx.flags.print_way_info)
		print_ways(all, 0);
}

int			main(int ac, char **av)
{
	t_all	all;

	ft_bzero(&all, sizeof(t_all));
	all.prog = VISU_HEX;
	all.exit = &visu_hex_clear_exit;
	parce_flags(&all, ac, av);
	parce_input(&all);
	parce_ants(&all);
	print_part(&all);
	visu_part(&all);
	return (0);
}
