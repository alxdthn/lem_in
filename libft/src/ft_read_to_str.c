/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 21:48:03 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/11 06:00:19 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t		ft_read_to_str(int fd, char **str, int b_size)
{
	char	buf[b_size];
	char	*tmp;
	ssize_t	size;
	int		ret;

	size = 0;
	*str = NULL;
	while ((ret = read(fd, buf, b_size)))
	{
		if (!(tmp = ft_memjoin(*str, buf, size, ret)))
			return (-1);
		ft_memdel((void **)str);
		*str = tmp;
		size += ret;
	}
	return (size);
}
