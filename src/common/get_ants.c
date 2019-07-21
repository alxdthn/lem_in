/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:15:12 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/21 18:15:24 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_ants(t_all *all)
{
	size_t	i;

	i = 0;
	if (!ft_isint(all->tmp.line))
		all->exit(all, ERROR, 2);
	all->ants = ft_satoi(all->tmp.line, &i);
	if (all->tmp.line[i])
		all->exit(all, ERROR, 2);
	all->switchs.ants = 1;
}
