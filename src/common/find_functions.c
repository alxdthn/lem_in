/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:27:39 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/26 17:23:57 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*find_room_by_name(t_list *rooms, char *name)
{
	t_list	*tmp;

	tmp = rooms;
	while (tmp)
	{
		if (!ft_strncmp(((t_room *)tmp->content)->name, name, ((t_room *)tmp->content)->name_len))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

t_door	*find_door_by_room_nb(t_room *room, int nb)
{
	t_list	*tmp;

	tmp = room->doors;
	while (tmp)
	{
		if (((t_door *)tmp->content)->room->nb == nb)
			return ((t_door *)tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

t_ant	*find_ant_by_name(t_list *ants, int name)
{
	t_list	*tmp;

	tmp = ants;
	while (tmp)
	{
		if (((t_ant *)tmp->content)->name == name)
			return ((t_ant *)tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}
