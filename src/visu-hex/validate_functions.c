/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 04:06:31 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 11:40:21 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	check_match_path(t_all *all, t_room *room_ptr)
{
	t_list	*way;

	way = all->ways;
	while (way)
	{
		if (WAY->path[1] == room_ptr)
		{
			WAY->ants++;
			return (1);
		}
		way = way->next;
	}
	return (0);
}

static int	init_ways(t_all *all)
{
	t_list	*ant;
	int		ret;

	ant = all->ants;
	ret = 0;
	while (ant)
	{
		if (!all->ways || !check_match_path(all, ANT->path->next->content))
			ret += init_new_way(all, ant, ret + 1);
		ant = ant->next;
	}
	return (ret);
}

void		validate_ways(t_all *all)
{
	t_list	*way;
	int		room;

	way = all->ways;
	while (way)
	{
		room = 1;
		while (WAY->path[room])
		{
			if (WAY->path[room]->way_nb && room < WAY->len - 1
			&& all->mlx.flags.print_err && all->mlx.flags.print_merge_err)
			{
				ft_putendl_fd("Error: paths merged!:", 2);
				print_way(find_way_by_nb(all->ways,
				WAY->path[room]->way_nb), 1);
				print_way(find_way_by_nb(all->ways, WAY->nb), 1);
				all->exit(all, NULL, 1);
			}
			WAY->path[room++]->way_nb = WAY->nb;
		}
		way = way->next;
	}
}

static char	*get_iteration_error(char *error, t_list *lst, int line_number)
{
	char	*res;

	if (!(res = ft_strjoin(error, get_line(lst, line_number))))
		return (NULL);
	return (res);
}

static int	list_check(t_list *a, t_list *b)
{
	if (!b)
		return (0);
	if (((t_room *)a->content)->nb > ((t_room *)b->content)->nb)
		return (1);
	return (0);
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

static void	validate_room_merge(t_all *all)
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

void		validate_iterations(t_all *all)
{
	int		i;
	int		ant;

	i = 0;
	validate_room_merge(all);
	while (all->iterations[i])
	{
		ant = 0;
		while (all->iterations[i][ant])
		{
			if (!all->iterations[i][ant]->name && all->mlx.flags.print_err)
				all->exit(all, get_iteration_error("Error: bad ant name: ",
				all->input, i), 3);
			if (all->iterations[i][ant + 1]
			&& all->iterations[i][ant]->name
			>= all->iterations[i][ant + 1]->name && all->mlx.flags.print_err)
				all->exit(all, get_iteration_error(
					"Error: repeat or not ordered ant in iteration: ",
				all->input, i), 3);
			ant++;
		}
		i++;
	}
}
