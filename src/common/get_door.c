/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:21:46 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 18:19:17 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	get_rooms(t_all *all, t_room **room_a, t_room **room_b)
{
	size_t	len_a;
	size_t	len_b;

	if (!(len_a = ft_strclen(all->tmp.line, '-'))
	|| all->tmp.line[len_a] != '-'
	|| !(*room_a = find_room_by_name(all->rooms, all->tmp.line)))
		all->exit(all, ERROR, 2);
	if (!(len_b = ft_strclen(all->tmp.line + len_a + 1, ' '))
	|| all->tmp.line[len_a + len_b + 1]
	|| !(*room_b = find_room_by_name(all->rooms, all->tmp.line + len_a + 1)))
		all->exit(all, ERROR, 2);
}

void		get_door(t_all *all)
{
	t_room	*room_a;
	t_room	*room_b;
	t_door	new_door;
	t_list	*node;

	get_rooms(all, &room_a, &room_b);
	if (find_room_in_doors_list_by_nb(room_a->doors, room_b->nb)
	|| find_room_in_doors_list_by_nb(room_b->doors, room_a->nb)
	|| room_a->nb == room_b->nb)
		return ;
	ft_bzero(&new_door, sizeof(t_door));
	new_door.room = room_b;
	if (!(node = ft_lstnew(&new_door, sizeof(t_door))))
		all->exit(all, ERROR, 2);
	ft_lstadd(&room_a->doors, node);
	new_door.room = room_a;
	if (!(node = ft_lstnew(&new_door, sizeof(t_door))))
		all->exit(all, ERROR, 2);
	ft_lstadd(&room_b->doors, node);
}
