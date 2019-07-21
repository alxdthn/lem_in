/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 18:03:36 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/21 18:31:12 by nalexand         ###   ########.fr       */
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
		else if (all->tmp.line[0] && !all->switchs.end)
			get_room(all);
		else if (all->tmp.line[0])
			get_door(all);
		else
			all->exit(all, ERROR, 2);
	}
	else
		all->exit(all, ERROR, 2);
}

void		parce_map(t_all *all)
{
	int		ret;

	while ((ret = get_next_line(0, &all->tmp.line)))
	{
		if (ret < 0 || !all->tmp.line)
			all->exit(all, ERROR, 2);
		parce_line(all);
		ft_lstadd(&all->out, ft_lstnew(all->tmp.line,
		1 + ft_strlen(all->tmp.line)));
		if (!all->out)
			all->exit(all, ERROR, 2);
		ft_strdel(&all->tmp.line);
	}
	if (!all->switchs.start || !all->switchs.end)
		all->exit(all, ERROR, 2);
}
