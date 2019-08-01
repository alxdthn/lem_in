/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_hex_clear_exit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:52:07 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 05:47:15 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	mlx_clear(t_all *all)
{
	if (all->mlx.ptr)
	{
		if (all->mlx.logo.ptr)
			mlx_destroy_image(all->mlx.ptr, all->mlx.logo.ptr);
		if (all->mlx.map.ptr)
			mlx_destroy_image(all->mlx.ptr, all->mlx.map.ptr);
		if (all->mlx.ants.ptr)
			mlx_destroy_image(all->mlx.ptr, all->mlx.ants.ptr);
		mlx_destroy_window(all->mlx.ptr, all->mlx.win);
		ft_memdel((void **)&all->mlx.ptr);
	}
}

void		visu_hex_clear_exit(t_all *all, char *message, int fd)
{
	all->out = all->out_head;
	all->input = all->input_head;
	mlx_clear(all);
	ft_lstdel(&all->rooms, clear_room);
	ft_lstdel(&all->ants, clear_ant);
	ft_lstdel(&all->out, ft_lstclear);
	ft_lstdel(&all->input, ft_lstclear);
	ft_lstdel(&all->ways, clear_way);
	ft_arraydel((void ***)&all->iterations);
	error_handle(all, message, fd);
	if (fd == 1)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}
