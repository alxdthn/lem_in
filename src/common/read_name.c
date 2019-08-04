/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 16:18:43 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/02 16:19:39 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t	read_name(char *name)
{
	size_t	len;

	len = 0;
	if (!name)
		return (0);
	while (name[len] && name[len] != ' ' && name[len] != '-')
		len++;
	return (len);
}
