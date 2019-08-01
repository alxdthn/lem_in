/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 15:52:59 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 05:08:03 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	*create_new_ant(t_all *all, int name)
{
	t_ant	new_ant;
	t_list	*ant;

	ft_bzero(&new_ant, sizeof(t_ant));
	if (!(new_ant.path = ft_lstnew(NULL, 0))
	|| !(ant = ft_lstnew(&new_ant, sizeof(t_ant))))
		all->exit(all, ERROR, 2);
	ANT->path->content = all->start_room;
	ANT->path->content_size = sizeof(t_room *);
	ANT->name = name;
	ft_lstadd(&all->ants, ant);
	return (ant);
}

static t_ant	*init_ant(t_all *all, size_t *i, size_t *j, char *line)
{
	t_list	*ant;
	t_list	*path;
	int		name;

	if (line[(*i)++] != 'L')
		all->exit(all, ERROR, 2);
	name = ft_satoi(line, i);
	if (line[(*i)++] != '-')
		all->exit(all, ERROR, 2);
	if (!(ant = find_ant_by_name(all->ants, name)))
		ant = create_new_ant(all, name);
	if (!(path = ft_lstnew(NULL, 0))
	|| !(path->content = find_room_by_name(all->rooms, line + *i)))
		all->exit(all, ERROR, 2);
	path->content_size = sizeof(t_room *);
	ft_lstpushback(&ANT->path, path);
	return (ant->content);
}

static void		read_ants_to_list(t_all *all, t_list *lines, size_t s)
{
	size_t	i;
	size_t	j;
	size_t	k;

	j = 0;
	if (!(all->iterations = (t_ant ***)ft_memalloc(sizeof(t_ant **) * (s + 1))))
		all->exit(all, ERROR, 2);
	while (lines)
	{
		i = 0;
		k = 0;
		if (!(all->iterations[j] = (t_ant **)ft_memalloc(sizeof(t_ant *)
		* (ft_strccount(LINE, 'L') + 1))))
			all->exit(all, ERROR, 2);
		while (LINE[i])
		{
			all->iterations[j][k++] = init_ant(all, &i, &j, LINE);
			while (LINE[i] && LINE[i] != ' ')
				i++;
			if (LINE[i] == ' ')
				i++;
		}
		j++;
		lines = lines->next;
	}
}

void			parce_ants(t_all *all)
{
	t_list	*node;
	size_t	iterations;

	iterations = 0;
	while (get_next_line(all->fd, &all->tmp.line) > 0)
	{
		if (!(node = ft_lstnew(NULL, 0)))
			all->exit(all, ERROR, 2);
		node->content = all->tmp.line;
		node->content_size = sizeof(char *);
		push_back(&all->input, node, &all->input_head);
		iterations++;
	}
	all->input = all->input_head;
	if (all->input)
		read_ants_to_list(all, all->input, iterations);
}
