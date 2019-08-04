/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:28:27 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/02 16:20:00 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	get_start_end(t_all *all, t_room *room)
{
	if (all->switchs.started)
	{
		room->type = START;
		all->switchs.started = 0;
		all->start_room = room;
	}
	else if (all->switchs.ended)
	{
		room->type = END;
		all->switchs.ended = 0;
		all->switchs.end = 1;
		all->end_room = room;
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

void		get_room(t_all *all, size_t i)
{
	t_room	new_room;
	t_list	*node;

	if (all->tmp.line[0] == 'L')
		all->exit(all, "Error: bad room", 2);
	if (check_name_match(all, all->tmp.line))
		return ;
	ft_bzero(&new_room, sizeof(t_room));
	new_room.visit = -1;
	new_room.name = all->tmp.line;
	new_room.nb = all->room_count++;
	i = read_name(all->tmp.line);
	new_room.name_len = i;
	if (!all->tmp.line[i++] || !ft_isint(all->tmp.line + i))
		all->exit(all, "Error: bad room coordinate", 2);
	new_room.x = ft_satoi(all->tmp.line, &i);
	if (!all->tmp.line[i++] || !ft_isint(all->tmp.line + i))
		all->exit(all, "Error: bad room coordinate", 2);
	new_room.y = ft_satoi(all->tmp.line, &i);
	if (all->tmp.line[i])
		all->exit(all, "Error: bad room coordinate", 2);
	if (!(node = ft_lstnew(&new_room, sizeof(t_room))))
		all->exit(all, ERROR, 2);
	get_start_end(all, node->content);
	ft_lstadd(&all->rooms, node);
}
