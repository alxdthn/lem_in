/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:21:46 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/26 17:26:21 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	get_rooms_from_name(t_all *all, t_room **room_a, t_room **room_b)
{
	size_t	len_a;
	size_t	len_b;

	if (!(len_a = ft_strclen(all->tmp.line, '-'))
	|| all->tmp.line[len_a] != '-'
	|| !(all->tmp.name = ft_strndup(all->tmp.line, len_a))
	|| !(*room_a = find_room_by_name(all->rooms, all->tmp.name)))
		all->exit(all, ERROR, 2);
	ft_strdel(&all->tmp.name);
	if (!(len_b = ft_strlen(all->tmp.line + len_a + 1))
	|| all->tmp.line[len_a + len_b + 1]
	|| !(all->tmp.name = ft_strndup(all->tmp.line + len_a + 1, len_b))
	|| !(*room_b = find_room_by_name(all->rooms, all->tmp.name)))
		all->exit(all, ERROR, 2);
	ft_strdel(&all->tmp.name);
}

void		get_door(t_all *all)
{
	t_room	*room_a;
	t_room	*room_b;
	t_door	clear_door;

	ft_bzero(&clear_door, sizeof(t_door));
	get_rooms_from_name(all, &room_a, &room_b);
	ft_lstadd(&room_a->doors, ft_lstnew(&clear_door, sizeof(t_door)));
	if (!(room_a->doors))
		all->exit(all, ERROR, 2);
	((t_door *)room_a->doors->content)->room = room_b;
	ft_lstadd(&room_b->doors, ft_lstnew(&clear_door, sizeof(t_door)));
	if (!(room_b->doors))
		all->exit(all, ERROR, 2);
	((t_door *)room_b->doors->content)->room = room_a;
}
