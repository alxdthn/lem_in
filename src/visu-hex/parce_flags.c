/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 05:11:10 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 06:18:15 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	read_flags(t_all *all, char c)
{
	if (c == 'v')
		all->mlx.flags.no_visu = 1;
	else if (c == 'w')
		all->mlx.flags.print_way_info = 1;
	else if (c == 'W')
		all->mlx.flags.print_way_info_path = 1;
	else if (c == 'e')
		all->mlx.flags.print_err = 1;
	else if (c == 'n')
		all->mlx.flags.normalize_map = 1;
	else if (c == 'i')
		all->mlx.flags.print_info = 1;
	else if (c == 'a')
		all->mlx.flags.print_rooms = 1;
	else if (c == 't')
		all->mlx.flags.print_iterations = 1;
	else
	{
		ft_putendl("Error: unknown flag!");
		put_usage();
		all->exit(all, NULL, 1);
	}
}

void		parce_flags(t_all *all, int ac, char **av)
{
	int		i;

	if (ac > 1)
	{
		if (av[1][0] == '-')
		{
			if (ft_strequ(av[1], "-help"))
			{
				put_usage();
				all->exit(all, NULL, 1);
			}
			i = 1;
			while (av[1][i])
				read_flags(all, av[1][i++]);
			if (ac == 3)
				all->fd = open(av[2], O_RDONLY);
		}
		else if (ac == 2)
			all->fd = open(av[1], O_RDONLY);
	}
}
