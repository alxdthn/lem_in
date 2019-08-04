/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_room_merge.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 12:05:27 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/02 12:40:16 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	list_check(t_list *a, t_list *b)
{
	if (!b)
		return (0);
	if (((t_room *)a->content)->nb > ((t_room *)b->content)->nb)
		return (1);
	return (0);
}

static void	init_node(t_all *all, t_list **lst, char *line, size_t i)
{
	t_list	*node;
	t_room	*room;

	room = find_room_by_name(all->rooms, line + i);
	if (room->type != END)
	{
		if (!(node = ft_lstnew(NULL, 0)))
		{
			ft_lstdel(lst, NULL);
			all->exit(all, ERROR, 2);
		}
		node->content = room;
		node->content_size = sizeof(t_room *);
		ft_lstadd(lst, node);
	}
	else if (room->type == START)
	{
		ft_lstdel(lst, NULL);
		ft_putendl_fd(line, 2);
		all->exit(all, "Error: ant in start!", 2);
	}
}

static void	check_match_rooms(t_all *all, t_list **lst, char *line)
{
	t_list	*room;

	ft_lstsort(*lst, list_check);
	room = *lst;
	while (room)
	{
		if (room->next && ((t_room *)room->content)->nb
		== ((t_room *)room->next->content)->nb)
		{
			ft_putstr_fd("Error: two ants in one room\n", 2);
			ft_putendl_fd(line, 2);
			ft_lstdel(lst, NULL);
			all->exit(all, NULL, 1);
		}
		room = room->next;
	}
	ft_lstdel(lst, NULL);
}

void		validate_room_merge(t_all *all)
{
	t_list	*lines;
	t_list	*lst;
	size_t	i;

	lines = all->input;
	lst = NULL;
	while (lines)
	{
		i = 0;
		while (LINE[i])
		{
			while (LINE[i] && LINE[i] != '-')
				i++;
			if (!LINE[i])
				break ;
			init_node(all, &lst, LINE, ++i);
		}
		check_match_rooms(all, &lst, LINE);
		lines = lines->next;
	}
}
