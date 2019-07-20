/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 04:28:55 by nalexand          #+#    #+#             */
/*   Updated: 2019/05/19 22:21:47 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*src;

	if ((src = malloc(size)) && size)
	{
		ft_bzero(src, size);
		return (src);
	}
	exit(EXIT_FAILURE);
}
