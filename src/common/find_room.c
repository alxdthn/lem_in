/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:27:39 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/21 18:27:53 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*find_room(t_all *all, char *name)
{
	t_list	*tmp;

	tmp = all->rooms;
	while (tmp)
	{
		if (ft_strequ(((t_room *)tmp->content)->name, name))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}
