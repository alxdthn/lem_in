/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 22:54:57 by skrystin          #+#    #+#             */
/*   Updated: 2019/07/30 00:41:18 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		send_ants(t_all *all, t_ways *way, int ant, int name_an)
{
	char	*str;
	t_room	**tmp;
	int		nmr;
	int		first;

	nmr = 1;
	while (ant > 0)
	{
		tmp = way->way;
	//	if (!tmp[nmr])
	//		break;
		first = nmr;
		while (nmr != 0 || first == nmr)
		{
			if (nmr > all->ways->len || name_an > all->ant_count)
			{
				nmr--;
				name_an++;
				continue;
			}
			ft_printf("L%d-%.*s", name_an, tmp[nmr]->name_len, tmp[nmr]->name);
			tmp[nmr]->ant = name_an;
			tmp[nmr - 1]->ant = 0;
			name_an++;
			nmr--;
			if (nmr == 0 || name_an >all->ant_count)
				ft_printf("\n");
			else
				ft_printf(" ");
		}
		nmr = first + 1;
		name_an = 1;
		if (!tmp[nmr])
			ant--;
	}
}