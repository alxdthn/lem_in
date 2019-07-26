/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 15:52:59 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/26 23:38:06 by nalexand         ###   ########.fr       */
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
		new_ant.x = all->mlx.start_room_x;
		new_ant.y = all->mlx.start_room_y;
		new_ant.is_counted = 0;
		new_ant.path = NULL;
		ft_lstadd(&all->ants, ft_lstnew(&new_ant, sizeof(t_ant)));
		ant = (t_ant *)all->ants->content;
	}
	node = ft_lstnew(NULL, 0);
	node->content = find_room_by_name(all->rooms, line + *i);
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
	t_list	*ant_lines;
	t_list	*node;
	size_t	iterations;

	iterations = 0;
	ant_lines = NULL;
	while (get_next_line(0, &all->tmp.line) > 0)
	{
		node = ft_lstnew(NULL, 0);
		node->content = all->tmp.line;
		ft_lstpushback(&ant_lines, node);
		iterations++;
	}
	read_ants_to_list(all, ant_lines, iterations);
	ft_lstdel(&ant_lines, ft_lstclear);
}
