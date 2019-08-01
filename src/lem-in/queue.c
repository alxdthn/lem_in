/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 21:57:04 by skrystin          #+#    #+#             */
/*   Updated: 2019/08/01 14:39:35 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
