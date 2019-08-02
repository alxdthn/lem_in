/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_iterations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 18:09:44 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/02 12:17:21 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	*get_iteration_error(char *error, t_list *lst, int line_number)
{
	char	*res;

	if (!(res = ft_strjoin(error, get_line(lst, line_number))))
		return (NULL);
	return (res);
}

void		validate_iterations(t_all *all)
{
	int		i;
	int		ant;

	i = 0;
	while (all->iterations[i])
	{
		ant = 0;
		while (all->iterations[i][ant])
		{
			if (!all->iterations[i][ant]->name)
				all->exit(all, get_iteration_error("Error: bad ant name: ",
				all->input, i), 3);
			if (all->iterations[i][ant + 1]
			&& all->iterations[i][ant]->name
			>= all->iterations[i][ant + 1]->name)
				all->exit(all, get_iteration_error(
					"Error: repeat or not ordered ant in iteration: ",
				all->input, i), 3);
			ant++;
		}
		i++;
	}
}
