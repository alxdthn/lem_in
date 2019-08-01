/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_new_way.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 05:35:26 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 05:37:29 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		init_new_way(t_all *all, t_list *ant, int counter)
{
	t_way	new_way;
	t_list	*node;
	t_list	*path;
	int		i;

	new_way.len = ft_lstcount(ANT->path);
	new_way.nb = counter;
	new_way.ants = 1;
	if (!(new_way.path = (t_room **)malloc(sizeof(t_room *)
	* (new_way.len + 1))))
		all->exit(all, ERROR, 2);
	new_way.path[new_way.len] = NULL;
	i = 0;
	path = ANT->path;
	while (i < new_way.len)
	{
		new_way.path[i++] = path->content;
		path = path->next;
	}
	if (!(node = ft_lstnew(&new_way, sizeof(t_way))))
		all->exit(all, ERROR, 2);
	ft_lstpushback(&all->ways, node);
	return (1);
}
