/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_clear_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:52:07 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 06:03:22 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		lem_in_clear_exit(t_all *all, char *message, int fd)
{
	all->out = all->out_head;
	all->ants = all->ants_head;
	ft_lstdel(&all->rooms, clear_room);
	ft_lstdel(&all->out, ft_lstclear);
	ft_lstdel(&all->ways, clear_way);
	error_handle(all, message, fd);
	if (fd == 1)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}
