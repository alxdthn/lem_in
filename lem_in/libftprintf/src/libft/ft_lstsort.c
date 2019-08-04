/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 10:53:01 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 10:53:24 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsort(t_list *lst, int (*f)(t_list *, t_list *))
{
	int		sorted;
	t_list	*cur;

	sorted = 0;
	while (sorted == 0)
	{
		cur = lst;
		sorted = 1;
		while (cur)
		{
			if (f(cur, cur->next) == 1)
			{
				ft_lstswap(cur, cur->next);
				sorted = 0;
			}
			cur = cur->next;
		}
	}
}
