/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 06:09:28 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/31 00:17:17 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	init_ants(t_all *all)
{
	t_ways	*current_way;
	t_list	*node;
	t_ant	new_ant;
	int		i;

	i = 1;
	current_way = all->ways;
	ft_bzero(&new_ant, sizeof(t_ant));
	while (i <= all->ant_count)
	{
		new_ant.name = i++;
		while (current_way)
		{
			if (current_way->ants)
			{
				new_ant.way = current_way;
				current_way->ants--;
				break ;
			}
			current_way = current_way->next;
			if (!current_way)
				current_way = all->ways;
		}
		if (!(node = ft_lstnew(&new_ant, sizeof(t_ant))))
			all->exit(all, ERROR, 2);
		push_back(&all->ants, node, &all->ants_head);
	}
	all->ants = all->ants_head;
}

static void	moove_ant(t_all *all, t_list *ant, char flag)
{
	if (ANT->way->way[ANT->position + 1]->visit_early == 0)
	{
		if (flag)
			ft_putchar(' ');
		ft_printf("L%d-%.*s", ANT->name,
		ANT->way->way[ANT->position + 1]->name_len,
		ANT->way->way[ANT->position + 1]->name);
		if (ANT->way->way[ANT->position + 1]->type != END)
			ANT->way->way[ANT->position + 1]->visit_early = 1;
		ANT->way->way[ANT->position++]->visit_early = 0;
	}
}

void	send_ants(t_all *all)
{
	t_list	*ant;
	t_ways	*ways;
	char	flag;

	flag = 1;
	clear_room_visit(all->mas_rom);
	init_ants(all);
	while (flag)
	{
		flag = 0;
		ant = all->ants;
		while (ant)
		{
			if (ANT->position != ANT->way->len)
			{
				moove_ant(all, ant, flag);
				flag = 1;
			}
			ant = ant->next;
		}
		if (flag)
			ft_putchar('\n');
	}
}
