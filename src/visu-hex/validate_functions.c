/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 04:06:31 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 18:25:41 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char		*get_iteration_error(char *error, t_list *lst, int line_number)
{
	char	*res;

	if (!(res = ft_strjoin(error, get_line(lst, line_number))))
		return (NULL);
	return (res);
}

static int	check_match_path(t_all *all, t_room *room_ptr)
{
	t_list	*way;

	way = all->ways;
	while (way)
	{
		if (WAY->path[1] == room_ptr)
		{
			WAY->ants++;
			return (1);
		}
		way = way->next;
	}
	return (0);
}

static int	init_ways(t_all *all)
{
	t_list	*ant;
	int		ret;

	ant = all->ants;
	ret = 0;
	while (ant)
	{
		if (!all->ways || !check_match_path(all, ANT->path->next->content))
			ret += init_new_way(all, ant, ret + 1);
		ant = ant->next;
	}
	return (ret);
}

void		validate_ways(t_all *all)
{
	t_list	*way;
	int		room;

	way = all->ways;
	while (way)
	{
		room = 1;
		while (WAY->path[room])
		{
			if (WAY->path[room]->way_nb && room < WAY->len - 1
			&& all->mlx.flags.print_err && all->mlx.flags.print_merge_err)
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
