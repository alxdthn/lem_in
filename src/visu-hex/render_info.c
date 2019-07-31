/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 15:46:43 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/31 01:34:59 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	get_count_of_ants(t_all *all)
{
	char	*tmp;

	tmp = ft_itoa(all->ant_count);
	all->mlx.info_count_of_ants = ft_strjoin("count of ants: ", tmp);
	ft_strdel(&tmp);
}

void		render_info(t_all *all)
{
	char	*line;
	char	*tmp;

	ft_strdel(&all->mlx.info_iter);
	ft_strdel(&all->mlx.info_ant_in_end);
	if (!all->mlx.info_count_of_ants)
		get_count_of_ants(all);
	tmp = ft_itoa(all->mlx.cur_iter);
	all->mlx.info_iter = ft_strjoin("iterations: ", tmp);
	ft_strdel(&tmp);
	tmp = ft_itoa(all->mlx.ants_in_end);
	all->mlx.info_ant_in_end = ft_strjoin("ants in end: ", tmp);
	ft_strdel(&tmp);
}
