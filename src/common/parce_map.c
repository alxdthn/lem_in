/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 18:03:36 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 06:00:50 by nalexand         ###   ########.fr       */
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
			if (!all->switchs.rooms)
				get_room(all);
			if (all->switchs.rooms)
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

	while ((ret = get_next_line(all->fd, &all->tmp.line)))
	{
		if (ret < 0 || !all->tmp.line)
			all->exit(all, ERROR, 2);
		if (all->prog == VISU_HEX && !*all->tmp.line)
		{
			ft_strdel(&all->tmp.line);
			return ;
		}
		if (!(node = ft_lstnew(NULL, 0)))
			all->exit(all, ERROR, 2);
		node->content = all->tmp.line;
		node->content_size = sizeof(char *);
		push_back(&all->out, node, &all->out_head);
		parce_line(all);
	}
	all->out = all->out_head;
	if (!all->switchs.start || !all->switchs.end)
		all->exit(all, ERROR, 2);
}
