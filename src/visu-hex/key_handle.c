/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 20:03:35 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/29 07:06:05 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			loop_hook(t_all *all)
{
	if (!all->mlx.working)
		return (0);
	render(all);
	return (0);
}

int			deal_key(int key, t_all *all)
{
	if (key == ESC)
		all->exit(all, NULL, 1);
	else if (key == ENTER)
		all->mlx.working = (all->mlx.working) ? 0 : 1;
	else if (key == SPACE)
		all->mlx.names = (all->mlx.names) ? 0 : 1;
	render(all);
	return (0);
}
