/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 18:15:02 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 18:17:07 by nalexand         ###   ########.fr       */
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
			ft_printf("name: L%d\n", all->iterations[i][j]->name);
			j++;
		}
		ft_printf("---------------\n");
		i++;
	}
}

void	print_info(t_all *all)
{
	ft_printf("min_path: %d\n", all->mlx.min_path_size);
	ft_printf("room: %d\n", all->mlx.room_radius);
	ft_printf("ant: %d\n", all->mlx.ant_radius);
	ft_printf("pixel: %d\n", all->mlx.pixel_size);
	ft_printf("size: %d\n", all->mlx.map_size);
}

void	print_way(t_list *way, char print_path)
{
	int		room;

	ft_printf("path №%d (len %d, ants %d sum %d): ",
	WAY->nb, WAY->len, WAY->ants, (WAY->ants) ? WAY->len + WAY->ants : 0);
	room = 0;
	while (print_path && WAY->path[room])
	{
		ft_printf("%.*s", WAY->path[room]->name_len, WAY->path[room]->name);
		if (WAY->path[room + 1])
			ft_printf(" -> ");
		++room;
	}
	ft_putchar('\n');
}

void	print_ways(t_all *all, char print_path)
{
	t_list	*way;

	way = all->ways;
	while (way)
	{
		print_way(way, print_path);
		way = way->next;
	}
}
