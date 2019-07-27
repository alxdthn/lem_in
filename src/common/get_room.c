/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:28:27 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/27 23:34:58 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	get_start_end(t_all *all, t_room *room)
{
	if (all->switchs.started)
	{
		room->type = START;
		all->switchs.started = 0;
	}
	else if (all->switchs.ended)
	{
		room->type = END;
		all->switchs.ended = 0;
		all->switchs.end = 1;
	}
}

static int	check_name_match(t_all *all, char *name)
{
	if (find_room_by_name(all->rooms, name))
	{
		if (all->switchs.ants && all->switchs.start && all->switchs.end)
		{
			all->switchs.rooms = 1;
			return (1);
		}
		else
			all->exit(all, ERROR, 2);
	}
	return (0);
}

void		get_room(t_all *all)
{
	size_t	i;
	t_room	new_room;
	t_list	*node;

	if (all->tmp.line[0] == 'L')
		all->exit(all, ERROR, 2);
	if (check_name_match(all, all->tmp.line))
		return ;
	ft_bzero(&new_room, sizeof(t_room));
	new_room.name = all->tmp.line;
	i = ft_strclen(all->tmp.line, ' ');
	new_room.name_len = i;
	get_start_end(all, &new_room);
	if (!all->tmp.line[i++] || !ft_isint(all->tmp.line + i))
		all->exit(all, ERROR, 2);
	new_room.x = ft_satoi(all->tmp.line, &i);
	if (!all->tmp.line[i++] || !ft_isint(all->tmp.line + i))
		all->exit(all, ERROR, 2);
	new_room.y = ft_satoi(all->tmp.line, &i);
	if (all->tmp.line[i])
		all->exit(all, ERROR, 2);
	if (!(node = ft_lstnew(&new_room, sizeof(t_room))))
		all->exit(all, ERROR, 2);		
	ft_lstadd(&all->rooms, node);
}
