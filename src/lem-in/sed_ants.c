/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sed_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 06:09:28 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/30 06:11:43 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	init_ants(t_all *all)
{
	t_ways	*current;
	t_list	*node;
	t_ant	new_ant;
	int		i;

	i = all->ant_count;
	current = all->ways;
	ft_bzero(&new_ant, sizeof(t_ant));
	while (i)
	{
		new_ant.name = i--;
		if (current)
			new_ant.way = current;
		else
		{
			new_ant.way = all->ways;
			current = all->ways;
		}
		current = current->next;
		if (!(node = ft_lstnew(&new_ant, sizeof(t_ant))))
			all->exit(all, ERROR, 2);
		ft_lstadd(&all->ants, node);
	}
}

static void	print_iterations(t_all *all)
{
	t_list	*ant;
	char	flag;

	ant = all->ants;
	flag = 1;
	while (ant)
	{
		if (((t_ant *)ant->content)->position
		&& ((t_ant *)ant->content)->position != ((t_ant *)ant->content)->way->len)
		{
			if (!flag)
				ft_printf(" ");
			ft_printf("L%d-%.*s", ((t_ant *)ant->content)->name,
			((t_ant *)ant->content)->way->way
			[((t_ant *)ant->content)->position]->name_len,
			((t_ant *)ant->content)->way->way
			[((t_ant *)ant->content)->position]->name);
			flag = 0;
		}
		ant = ant->next;
	}
	ft_printf("\n");
}

static void	moove_ant(t_all *all, t_list *ant)
{
	if (((t_ant *)ant->content)->way->way
	[((t_ant *)ant->content)->position + 1]->ant == NULL)
	{
		if (((t_ant *)ant->content)->way->way
		[((t_ant *)ant->content)->position + 1]->type == END)
		{
			ft_printf("L%d-%.*s ", ((t_ant *)ant->content)->name,
			all->end_room->name_len, all->end_room->name);
			((t_ant *)ant->content)->way->way
			[((t_ant *)ant->content)->position++]->ant = NULL;
			return ;
		}
		((t_ant *)ant->content)->way->way
		[((t_ant *)ant->content)->position + 1]->ant = ant;
		((t_ant *)ant->content)->way->way
		[((t_ant *)ant->content)->position++]->ant = NULL;
	}
}

void	send_ants(t_all *all)
{
	t_list	*ant;
	t_ways	*ways;
	char	flag;

	flag = 1;
	init_ants(all);
	while (flag)
	{
		flag = 0;
		ant = all->ants;
		while (ant)
		{
			if (((t_ant *)ant->content)->position
			!= ((t_ant *)ant->content)->way->len)
			{
				moove_ant(all, ant);
				flag = 1;
			}
			ant = ant->next;
		}
		print_iterations(all);
	}
}
