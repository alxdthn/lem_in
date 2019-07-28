/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 15:52:59 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/28 06:15:56 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_ant	*init_ant(t_all *all, size_t *i, size_t *j, char *line)
{
	int		name;
	t_ant	*ant;
	t_ant	new_ant;
	t_list	*node;

	if (line[(*i)++] != 'L')
		all->exit(all, ERROR, 2);
	name = ft_satoi(line, i);
	if (line[(*i)++] != '-')
		all->exit(all, ERROR, 2);
	if (!(ant = find_ant_by_name(all->ants, name)))
	{
		new_ant.name = name;
		new_ant.is_counted = 0;
		new_ant.in_place = 0;
		new_ant.path = node = ft_lstnew(NULL, 0);
		new_ant.path->content = all->start_room;
		ft_lstadd(&all->ants, ft_lstnew(&new_ant, sizeof(t_ant)));
		ant = (t_ant *)all->ants->content;
	}
	node = ft_lstnew(NULL, 0);
	if (!(node->content = find_room_by_name(all->rooms, line + *i)))
		all->exit(all, ERROR, 2);
	ft_lstpushback(&ant->path, node);
	return (ant);
}

void	read_ants_to_list(t_all *all, t_list *lines, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	j = 0;
	all->iterations = (t_ant ***)ft_memalloc(sizeof(t_ant **) * (size + 1));
	while (lines)
	{
		i = 0;
		k = 0;
		all->iterations[j] = (t_ant **)ft_memalloc(sizeof(t_ant *) * (ft_strccount((char *)lines->content, 'L') + 1));
		while (((char *)lines->content)[i])
		{
			all->iterations[j][k++] = init_ant(all, &i, &j, (char *)lines->content);
			while (((char *)lines->content)[i] && ((char *)lines->content)[i] != ' ')
				i++;
			if (((char *)lines->content)[i] == ' ')
				i++;
		}
		j++;
		ft_memdel(&lines->content);
		lines = lines->next;
	}
}

void	parce_ants(t_all *all)
{
	t_list	*node;
	size_t	iterations;

	iterations = 0;
	while (get_next_line(0, &all->tmp.line) > 0)
	{
		if (!(node = ft_lstnew(NULL, 0)))
			all->exit(all, ERROR, 2);
		node->content = all->tmp.line;
		ft_lstpushback(&all->out, node);
		iterations++;
	}
	read_ants_to_list(all, all->out, iterations);
}
