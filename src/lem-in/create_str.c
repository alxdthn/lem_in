/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 22:54:57 by skrystin          #+#    #+#             */
/*   Updated: 2019/07/29 00:15:35 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_create_str(t_all *all, t_ways *way, int ant, int name_an)
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