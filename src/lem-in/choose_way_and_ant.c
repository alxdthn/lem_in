/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_way_and_ant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 17:22:59 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/01 03:15:37 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	remove_way(t_list *prev, t_list **dep, int i, int stop)
{
	while (i < stop)
	{
		WAY_N((*dep))->path[i]->visit_early = '\0';
		i++;
	}
	prev->next = (*dep)->next;
	free(WAY_N((*dep))->path);
	free(*dep);
	*dep = NULL;
}

void	do_independent_this_ways(t_all *all, t_list *dep, t_list *prev, int i)
{
	if (!dep->next)
		return ;
	while (dep)
	{
		while (WAY_N(dep)->path[i])
		{
			if (WAY_N(dep)->path[i]->visit_early)
			{
				remove_way(prev, &dep, 0, i);
				break ;
			}
			WAY_N(dep)->path[i]->visit_early = '1';
			i++;
		}
		if (dep != prev)
			prev = prev->next;
		if (prev)
			dep = prev->next;
	}
}

int		distribute_ants_to_ways(t_all *all, t_list *way, t_list *begin, int i)
{
	int	ants;

	ants = all->ant_count;
//	ft_printf("begin - %d\n", begin->ants);
	while (ants > 0)
	{
		if (!way->next)
		{
			WAY->ants++;
			ants--;
			way = begin;
			continue;
		}
		while (WAY->len + WAY->ants <= WAY_P(next)->len + WAY_P(next)->ants
		&& (WAY->len + WAY->ants < WAY_N(begin)->len + WAY_N(begin)->ants || way == begin))
		{
			WAY->ants++;
			ants--;
		}
		if (way != begin && WAY->len + WAY->ants == WAY_N(begin)->len + WAY_N(begin)->ants)
			way = begin;
		else
			way = way->next;
	}
	return (WAY_N(begin)->len + WAY_N(begin)->ants);
}

void	choose_ways(t_all *all, int ant, t_list *indep, t_list *dep)
{
	int indep_move;
	int	dep_move;

	clear_room_visit(all->mas_rom);
	do_independent_this_ways(all, dep, dep, 0);
	indep_move = distribute_ants_to_ways(all, indep, indep, 0);
	dep_move = distribute_ants_to_ways(all, dep, dep, 0);
	if (indep_move > dep_move)
	{
		delete_ways(all, 0);
		all->ways = all->dependent_ways;
		all->dependent_ways = 0;
	}
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