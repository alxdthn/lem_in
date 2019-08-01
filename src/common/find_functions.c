/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:27:39 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 18:17:55 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*find_room_by_name(t_list *rooms, char *name)
{
	t_list	*tmp;

	tmp = rooms;
	while (tmp)
	{
		if (name_cmp(((t_room *)tmp->content)->name, name))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

t_room	*find_room_in_doors_list_by_nb(t_list *rooms, int nb)
{
	t_list	*tmp;

	tmp = rooms;
	while (tmp)
	{
		if (((t_door *)tmp->content)->room->nb == nb)
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

t_list	*find_ant_by_name(t_list *ants, int name)
{
	t_list	*ant;

	ant = ants;
	while (ant)
	{
		if (ANT->name == name)
			return (ant);
		ant = ant->next;
	}
	return (NULL);
}

t_list	*find_way_by_nb(t_list *way, int nb)
{
	while (way)
	{
		if (WAY->nb == nb)
			return (way);
		way = way->next;
	}
	return (NULL);
}
