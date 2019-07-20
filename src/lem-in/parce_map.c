/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 18:03:36 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/20 18:08:01 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	parce_map(t_all *all)
{
	int		ret;

	while ((ret = get_next_line(0, &all->line)))
	{
		if (ret < 0 || !all->line)
			all->exit(all, ERROR, 2);
		ft_putstr(all->line);
		ft_strdel(&all->line);
	}
}
