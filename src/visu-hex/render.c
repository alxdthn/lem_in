/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 20:10:20 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/26 21:26:07 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	put_logo(t_all *all)
{
	if (all->mlx.logo.ptr)
		mlx_put_image_to_window(all->mlx.ptr,
		all->mlx.win, all->mlx.logo.ptr, 10, 10);
}

void		render(t_all *all)
{
	mlx_put_image_to_window(all->mlx.ptr, all->mlx.win, all->mlx.map.ptr, 0, 0);
	put_ants(all);
	put_logo(all);
}
