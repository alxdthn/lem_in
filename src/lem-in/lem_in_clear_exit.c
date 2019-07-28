/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_clear_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:52:07 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/29 01:56:42 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	clear_room(void *room, size_t size)
{
	ft_lstdel(&((t_room *)room)->doors, ft_lstclear);
	ft_memdel((void **)&room);
}

void		lem_in_clear_exit(t_all *all, char *message, int fd)
{
	ft_lstdel(&all->rooms, clear_room);
	ft_lstdel(&all->out, ft_lstclear);
	if (message)
		ft_putendl_fd(message, fd);
	if (fd == 1)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}
