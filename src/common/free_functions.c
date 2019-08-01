/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 05:44:17 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 17:08:35 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clear_room(void *room, size_t size)
{
	
	ft_lstdel(&((t_room *)room)->doors, ft_lstclear);
	free(room);
}

void	clear_ant(void *ant, size_t size)
{
	ft_lstdel(&((t_ant *)ant)->path, NULL);
	free(ant);
}

void	clear_way(void *way, size_t size)
{
	free(((t_way *)way)->path);
	free(way);
}

void	error_handle(t_all *all, char *message, int fd)
{
	if (message)
	{
		if (fd == 3)
		{
			fd = 2;
			ft_putendl_fd(message, fd);
			ft_strdel(&message);
		}
		else
			ft_putendl_fd(message, fd);
	}
}
