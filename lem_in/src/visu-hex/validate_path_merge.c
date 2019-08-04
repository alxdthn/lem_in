/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path_merge.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 04:06:31 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/02 12:41:21 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		validate_path_merge(t_all *all)
{
	t_list	*way;
	int		room;

	way = all->ways;
	while (way)
	{
		room = 1;
		while (WAY->path[room])
		{
			if (WAY->path[room]->way_nb && room < WAY->len - 1)
			{
				ft_putendl_fd("Error: paths merged!:", 2);
				print_way(find_way_by_nb(all->ways,
				WAY->path[room]->way_nb), 1);
				print_way(find_way_by_nb(all->ways, WAY->nb), 1);
				all->exit(all, NULL, 1);
			}
			WAY->path[room++]->way_nb = WAY->nb;
		}
		way = way->next;
	}
}
