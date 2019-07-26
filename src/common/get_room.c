/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:28:27 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/26 17:08:00 by nalexand         ###   ########.fr       */
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

static void	check_name_match(t_all *all, char *name)
{
	t_list	*tmp;

	tmp = all->rooms->next;
	while (tmp)
	{
		if (ft_strequ(((t_room *)tmp->content)->name, name))
			all->exit(all, ERROR, 2);
		tmp = tmp->next;
	}
}

void		get_room(t_all *all)
{
	size_t	i;
	t_room	clear_room;

	ft_bzero(&clear_room, sizeof(t_room));
	ft_lstadd(&all->rooms, ft_lstnew(&clear_room, sizeof(t_room)));
	get_start_end(all, (t_room *)all->rooms->content);
	i = ft_strclen(all->tmp.line, ' ');
	((t_room *)all->rooms->content)->name = ft_strndup(all->tmp.line, i);
	((t_room *)all->rooms->content)->name_len = i;
	if (((t_room *)all->rooms->content)->name[0] == 'L')
		all->exit(all, ERROR, 2);
	check_name_match(all, ((t_room*)all->rooms->content)->name);
	if (!all->tmp.line[i++] || !ft_isint(all->tmp.line + i))
		all->exit(all, ERROR, 2);
	((t_room *)all->rooms->content)->x = ft_satoi(all->tmp.line, &i);
	if (!all->tmp.line[i++] || !ft_isint(all->tmp.line + i))
		all->exit(all, ERROR, 2);
	((t_room *)all->rooms->content)->y = ft_satoi(all->tmp.line, &i);
	if (all->tmp.line[i])
		all->exit(all, ERROR, 2);
}
