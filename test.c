/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 03:58:27 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/28 04:44:56 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		costyl(char c)
{
	if (c == ' ')
		return (0);
	else if (c == '\0')
		return (0);
	else if (c == '-')
		return (0);
	return (1);
}

int		name_cmp(const char *s1, const char *s2)
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

int		main(void)
{
	char	*s1;
	char 	*s2;

	s1 = "10";
	s2 = "10-";
	ft_printf("%d\n", name_cmp(s1, s2));
}
