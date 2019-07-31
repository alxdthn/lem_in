/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:21:11 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/31 01:01:33 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_out(t_list *list)
{
	while (list)
	{
		ft_putendl(list->content);
		list = list->next;
	}
	ft_putchar('\n');
}

void	clear_room_visit(t_room **mas_rom)
{
	int		i;

	i = 0;
	while (mas_rom[i])
		mas_rom[i++]->visit_early = '\0';
}

int			main(void)
{
	t_all	all;

	ft_bzero(&all, sizeof(t_all));
	all.prog = LEM_IN;
	all.exit = &lem_in_clear_exit;
	parce_input(&all);
	print_out(all.out);
	get_ways(&all, all.rooms);
	send_ants(&all);
	//print_ways(&all);
	//print_ants(&all);
	all.exit(&all, NULL, 1);
	return (0);
}
