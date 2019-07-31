/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:27:39 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/31 00:52:36 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		costyl(char c)
{
	if (c == ' ')
		return (0);
	else if (c == '\0')
		return (0);
	else if (c == '-')
		return (0);
	return (1);
}

int		name_cmp(const char *s1, const char *s2)
{
	size_t		i;

	i = 0;
	while (costyl(s1[i]) || costyl(s2[i]))
	{
		if (s1[i] != s2[i])
			return (0);
		++i;
	}
	return (1);
}

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
