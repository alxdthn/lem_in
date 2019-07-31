/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 20:10:20 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/31 01:39:35 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		render(t_all *all)
{
	put_map(all);
	if (all->mlx.names)
		put_names(all);
	if (all->iterations[all->mlx.cur_iter])
	{
		if (all->mlx.working)
			render_ants(all);
		put_ants(all);
	}
	put_info(all);
	put_logo(all);
}
