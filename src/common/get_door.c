/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:21:46 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/27 23:17:10 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	get_rooms_from_name(t_all *all, t_room **room_a, t_room **room_b)
{
	size_t	len_a;
	size_t	len_b;

	if (!(len_a = ft_strclen(all->tmp.line, '-'))
	|| all->tmp.line[len_a] != '-'
	|| !(*room_a = find_room_by_name(all->rooms, all->tmp.line)))
		all->exit(all, ERROR, 2);
	if (!(len_b = ft_strlen(all->tmp.line + len_a + 1))
	|| all->tmp.line[len_a + len_b + 1]
	|| !(*room_b = find_room_by_name(all->rooms, all->tmp.line + len_a + 1)))
		all->exit(all, ERROR, 2);
}

void		get_door(t_all *all)
{
	t_room	*room_a;
	t_room	*room_b;
	t_door	clear_door;
	t_list	*node;

	ft_bzero(&clear_door, sizeof(t_door));
	get_rooms_from_name(all, &room_a, &room_b);
	clear_door.room = room_b;
	if (!(node = ft_lstnew(&clear_door, sizeof(t_door))))
		all->exit(all, ERROR, 2);
	ft_lstadd(&room_a->doors, node);
	clear_door.room = room_a;
	if (!(node = ft_lstnew(&clear_door, sizeof(t_door))))
		all->exit(all, ERROR, 2);		
	ft_lstadd(&room_b->doors, node);
}
