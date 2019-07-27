/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_hex_clear_exit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:52:07 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/27 16:05:11 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	clear_room(void *room, size_t size)
{
	ft_strdel(&((t_room *)room)->name);
	ft_lstdel(&((t_room *)room)->doors, ft_lstclear);
	ft_memdel((void **)&room);
}

void		visu_hex_clear_exit(t_all *all, char *message, int fd)
{
	ft_strdel(&all->tmp.line);
	ft_strdel(&all->tmp.name);
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
	if (all->rooms)
		ft_lstdel(&all->rooms, clear_room);
	if (all->ants)
		ft_lstdel(&all->rooms, ft_lstclear);
	if (all->iterations)
		ft_arraydel((void ***)&all->iterations);
	if (message)
		ft_putendl_fd(message, fd);
	if (fd == 1)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}
