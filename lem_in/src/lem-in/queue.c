/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 21:57:04 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/01 15:39:51 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		create_mas(t_all *all, t_list *begin)
{
	int		i;

	i = all->room_count - 2;
	if (!(all->mas_rom = (t_room **)malloc(sizeof(t_room *)
	* (all->room_count + 1))))
		all->exit(all, ERROR, 2);
	all->mas_rom[all->room_count] = NULL;
	while (begin)
	{
		if (((t_room *)begin->content)->type == START)
			all->mas_rom[0] = (t_room *)begin->content;
		else if (((t_room *)begin->content)->type == END)
			all->mas_rom[all->room_count - 1] = (t_room *)begin->content;
		else
		{
			all->mas_rom[i] = begin->content;
			i--;
		}
		begin = begin->next;
	}
}

void		q_push_back(t_room *room, t_que **q, t_all *all)
{
	t_que	*last;
	t_que	*begin;

	if (!(last = (t_que *)malloc(sizeof(t_que))))
		all->exit(all, ERROR, 2);
	last->room = room;
	last->next = 0;
	if (!*q)
	{
		(*q) = last;
		return ;
	}
	begin = *q;
	while (begin->next)
		begin = begin->next;
	begin->next = last;
}

void		del_first(t_que **q)
{
	t_que	*begin;

	if (!*q)
		return ;
	begin = (*q)->next;
	free(*q);
	*q = begin;
}
