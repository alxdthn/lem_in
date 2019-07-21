/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_clear_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:52:07 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/21 17:51:16 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clear_room(void *room, size_t size)
{
	ft_strdel(&((t_room *)room)->name);
	ft_lstdel(&((t_room *)room)->doors, ft_lstclear);
	ft_memdel((void **)&room);
}

void	lem_in_clear_exit(t_all *all, char *message, int fd)
{
	ft_strdel(&all->tmp.line);
	ft_strdel(&all->tmp.name);
	if (all->rooms)
		ft_lstdel(&all->rooms, clear_room);
	if (all->out)
		ft_lstdel(&all->out, ft_lstclear);
	if (message)
		ft_putendl_fd(message, fd);
	if (fd == 1)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}
