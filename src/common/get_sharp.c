/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sharp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:13:46 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/02 14:22:30 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_sharp(t_all *all)
{
	if (all->tmp.line[1] == '#')
	{
		if (!all->switchs.start && (ft_strequ("start", all->tmp.line + 2)))
		{
			if (all->switchs.started || all->switchs.ended)
				all->exit(all, "Error: command fail", 2);
			all->switchs.start = 1;
			all->switchs.started = 1;
		}
		else if (!all->switchs.end && (ft_strequ("end", all->tmp.line + 2)))
		{
			if (all->switchs.started || all->switchs.ended)
				all->exit(all, "Error: command fail", 2);
			all->switchs.ended = 1;
		}
		else
			all->exit(all, "Error: command fail", 2);
	}
}
