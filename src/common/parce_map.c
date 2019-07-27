/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 18:03:36 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/27 22:54:34 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	parce_line(t_all *all)
{
	if (!all->switchs.ants)
		get_ants(all);
	else if (all->switchs.ants)
	{
		if (all->tmp.line[0] == '#')
			get_sharp(all);
		else
		{
			if (all->tmp.line[0] && !all->switchs.rooms)
				get_room(all);
			if (all->tmp.line[0] && all->switchs.rooms)
				get_door(all);
		}
	}
	else
		all->exit(all, ERROR, 2);
}

void		parce_input(t_all *all)
{
	int		ret;
	t_list	*node;

	while ((ret = get_next_line(0, &all->tmp.line)))
	{
		if (ret < 0 || !all->tmp.line)
			all->exit(all, ERROR, 2);
		if (all->prog == VISU_HEX && !*all->tmp.line)
			return ;
		parce_line(all);
		if (all->prog == LEM_IN)
		{
			if (!(node = ft_lstnew(NULL, 0)))
				all->exit(all, ERROR, 2);
			node->content = all->tmp.line;
			ft_lstadd(&all->out, node);
		}
	}
	if (!all->switchs.start || !all->switchs.end)
		all->exit(all, ERROR, 2);
}
