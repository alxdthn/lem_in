/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 18:03:36 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/20 21:46:56 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	get_sharp(t_all *all)
{
	if (all->tmp.line[1] == '#')
	{
		if (!all->switchs.start && ft_strequ("start", all->tmp.line + 2))
		{
			all->switchs.start = 1;
			all->switchs.started = 1;
		}
		else if (!all->switchs.end && ft_strequ("end", all->tmp.line + 2))
			all->switchs.ended = 1;
		else
			all->exit(all, ERROR, 2);
	}
}

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

	tmp = all->rooms;
	while (tmp)
	{
		if (ft_strequ(((t_room *)tmp->content)->name, name))
			all->exit(all, ERROR, 2);
		tmp = tmp->next;
	}
}

static void	get_room(t_all *all)
{
	size_t	i;

	if (!(all->tmp.room = (t_room *)ft_memalloc(sizeof(t_room))))
		all->exit(all, ERROR, 2);
	get_start_end(all, all->tmp.room);
	i = ft_strclen(all->tmp.line, ' ');
	if (!(all->tmp.room->name = ft_strndup(all->tmp.line, i)))
		all->exit(all, ERROR, 2);
	check_name_match(all, all->tmp.room->name);
	if (!all->tmp.line[i++] || !ft_isint(all->tmp.line + i))
		all->exit(all, ERROR, 2);
	all->tmp.room->x = ft_satoi(all->tmp.line, &i);
	if (!all->tmp.line[i++] || !ft_isint(all->tmp.line + i))
		all->exit(all, ERROR, 2);
	all->tmp.room->y = ft_satoi(all->tmp.line, &i);
	if (all->tmp.line[i])
		all->exit(all, ERROR, 2);
	ft_lstadd(&all->rooms, ft_lstnew(all->tmp.room, sizeof(t_room)));
	if (!all->rooms)
		all->exit(all, ERROR, 2);
	if (!(((t_room *)all->rooms->content)->name = ft_strdup(all->tmp.room->name)))
		all->exit(all, ERROR, 2);
	ft_strdel(&all->tmp.room->name);
	ft_memdel((void **)&all->tmp.room);
}

static void	get_link(t_all *all)
{
	char	*name_a;
	char	*name_b;
	size_t	len;

	if (!(len = ft_strclen(all->tmp.line, '-'))
	|| all->tmp.line[len] != '-')
		all->exit(all, ERROR, 2);
	if (!(name_a = ft_strndup(all->tmp.line, len)))
		all->exit(all, ERROR, 2);
	// KONEC
	if ()
}

static void	parce_tmp(t_all *all)
{
	if (all->tmp.line[0] == '#')
		get_sharp(all);
	else if (all->tmp.line[0] && !all->switchs.end)
		get_room(all);
	else if (all->tmp.line[0])
		get_link(all);
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
		parce_tmp(all);
		ft_printf("%s\n", all->tmp.line);
		ft_strdel(&all->tmp.line);
	}
}
