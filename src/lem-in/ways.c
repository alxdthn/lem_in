/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 19:17:19 by skrystin          #+#    #+#             */
/*   Updated: 2019/07/30 00:16:02 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void        ft_push_front_way(t_all *all, t_ways **ways, t_room *room, int len)
{
    if (!*ways)
        return ;
    if (!(*ways)->way)
    {
        if (!((*ways)->way = (t_room **)malloc((sizeof(t_room *) * (len + 1)))))
            all->exit(all, ERROR, 2);
        (*ways)->way[len] = 0;
    }
    (*ways)->way[room->visit] = room;
}

void        ft_add_way(t_all *all, t_ways *new)
{
    t_ways  *tmp;

    if (!all->ways)
        all->ways = new;
    else
    {
        tmp = all->ways;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

void		ft_create_ways(t_all *all, int i, int end)
{
	t_ways	*new;
	t_list	*tmp;
	t_door	*door;

	if (!(new = (t_ways *)malloc(sizeof(t_ways))))
		all->exit(all, ERROR, 2);
	new->len = all->mas_rom[end]->visit;
	new->next = 0;
    new->way = 0;
	ft_push_front_way(all, &new, all->mas_rom[end], new->len + 1);
	while (i > 0)
	{
		tmp = new->way[i]->doors;
		door = tmp->content;
		while (door->room->visit != i - 1)
		{
			tmp = tmp->next;
			door = tmp->content;
		}
		ft_push_front_way(all, &new, door->room, new->len);
		i--;
	}
	ft_add_way(all, new);
    i = 0;
    while (new->way[i])
    {
        ft_putstr(new->way[i]->name);
        ft_putchar('\n');
        i++;
    }
	ft_putchar('\n');
}
