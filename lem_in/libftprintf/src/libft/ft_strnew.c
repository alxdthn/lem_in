/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 23:15:01 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/31 04:25:27 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	if ((size + 1) == 0)
		return (NULL);
	if (!(str = malloc(size + 1)))
		return (NULL);
	str[size] = '\0';
	return (str);
}
