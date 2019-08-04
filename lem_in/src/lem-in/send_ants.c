/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 06:09:28 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 18:04:38 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	init_ants(t_all *all, int i, t_list *way, t_list *node)
{
	t_ant	new_ant;

	ft_bzero(&new_ant, sizeof(t_ant));
	while (i <= all->ant_count)
	{
		new_ant.name = i++;
		while (way)
		{
			if (WAY->ants)
			{
				new_ant.way = way;
				WAY->ants--;
				if (!(way = way->next))
					way = all->ways;
				break ;
			}
			if (!(way = way->next))
				way = all->ways;
		}
		if (!(node = ft_lstnew(&new_ant, sizeof(t_ant))))
			all->exit(all, ERROR, 2);
		push_back(&all->ants, node, &all->ants_head);
	}
	all->ants = all->ants_head;
}

static void	moove_ant(t_all *all, t_list *ant, char flag)
{
	if (ANT_WAY->path[ANT->position + 1]->visit_early == 0)
	{
		if (flag)
			ft_putchar(' ');
		ft_printf("L%d-%.*s", ANT->name,
		ANT_WAY->path[ANT->position + 1]->name_len,
		ANT_WAY->path[ANT->position + 1]->name);
		if (ANT_WAY->path[ANT->position + 1]->type != END)
			ANT_WAY->path[ANT->position + 1]->visit_early = 1;
		ANT_WAY->path[ANT->position++]->visit_early = 0;
	}
}

void		send_ants(t_all *all)
{
	t_list	*ant;
	t_list	*way;
	char	flag;

	flag = 1;
	clear_room_visit(all->mas_rom);
	init_ants(all, 1, all->ways, NULL);
	while (flag)
	{
		flag = 0;
		ant = all->ants;
		while (ant)
		{
			if (ANT->position != ANT_WAY->len)
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
