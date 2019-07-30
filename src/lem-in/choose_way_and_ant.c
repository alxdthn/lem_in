/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_way_and_ant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 17:22:59 by skrystin          #+#    #+#             */
/*   Updated: 2019/07/31 02:41:50 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	remove_way(t_ways *prev, t_ways **dep, int i, int stop)
{
	while (i < stop)
	{
		(*dep)->way[i]->visit_early = '\0';
		i++;
	}
	prev->next = (*dep)->next;
	free((*dep)->way);
	free(*dep);
	*dep = NULL;
}

void	do_independent_this_ways(t_all *all, t_ways *dep, t_ways *prev, int i)
{
	if (!dep->next)
		return ;
	while (dep)
	{
		while (dep->way[i])
		{
			if (dep->way[i]->visit_early)
			{
				remove_way(prev, &dep, 0, i);
				break ;
			}
			dep->way[i]->visit_early = '1';
			i++;
		}
		if (dep != prev)
			prev = prev->next;
		if (prev)
			dep = prev->next;
	}
}

int		distribute_ants_to_ways(t_all *all, t_ways *way, t_ways *begin, int i)
{
	int	ants;
	int	sum;

	ants = all->ant_count;
	sum = begin->len + 1;
	ft_printf("begin - %d\n", begin->ants);
	while (ants > 0)
	{
		while (way)
		{
			if (sum > way->len + way->ants)
			{
				way->ants++;
				ants--;
			}
			way = way->next;
		}
		way = begin;
		sum++;
	}
	return (begin->len + begin->ants);
}

int		choose_ways(t_all *all, int ant, t_ways *indep, t_ways *dep)
{
	int indep_move;
	int	dep_move;

//	if (is_independent_ways(all, all->mas_rom, 0))
		clear_room_visit(all->mas_rom);
	do_independent_this_ways(all, dep, dep, 0);
	delete_ants_from_path(indep, dep);
	indep_move = distribute_ants_to_ways(all, indep, indep, 0);
	dep_move = distribute_ants_to_ways(all, dep, dep, 0);
	if (indep_move > dep_move)
	{
		if (dep == all->dependent_ways)
		{
//			clear_room_visit(all->mas_rom);
			delete_ways(all, 0);
			all->ways = all->dependent_ways;
			all->dependent_ways = 0;
		}
		ft_printf("indep - %d, dep - %d\n", indep_move, dep_move);
		return (0);
	}
	return (1);
}

/*
25
##start
A 0 10
B 10 0
C 20 0
D 20 10
E 10 10
F 15 20
G 30 20
##end
H 30 10
A-B
A-E
B-C
C-D
E-D
E-F
D-F
F-G
G-H
D-H
 */