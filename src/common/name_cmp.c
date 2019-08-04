/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_cmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 18:17:42 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/02 14:22:33 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	costyl(char c)
{
	if (c == ' ')
		return (0);
	else if (c == '\0')
		return (0);
	else if (c == '-')
		return (0);
	return (1);
}

int			name_cmp(const char *s1, const char *s2)
{
	size_t		i;

	i = 0;
	while (costyl(s1[i]) || costyl(s2[i]))
	{
		if (s1[i] != s2[i])
			return (0);
		++i;
	}
	return (1);
}
