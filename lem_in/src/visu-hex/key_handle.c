/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 20:03:35 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 04:29:25 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			loop_hook(t_all *all)
{
	if (!all->mlx.flags.working)
		return (0);
	render(all);
	return (0);
}

int			deal_key(int key, t_all *all)
{
	if (key == ESC)
		all->exit(all, NULL, 1);
	else if (key == ENTER)
		all->mlx.flags.working = (all->mlx.flags.working) ? 0 : 1;
	else if (key == SPACE)
		all->mlx.flags.names = (all->mlx.flags.names) ? 0 : 1;
	render(all);
	return (0);
}
