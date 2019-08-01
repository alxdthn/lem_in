/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:21:11 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 15:01:41 by skrystin         ###   ########.fr       */
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

void		clear_room_visit(t_room **mas_rom)
{
	int		i;

	i = 0;
	while (mas_rom[i])
		mas_rom[i++]->visit_early = '\0';
}

int			main(int ac, char **av)
{
	t_all	all;

	ft_bzero(&all, sizeof(t_all));
	all.prog = LEM_IN;
	all.exit = &lem_in_clear_exit;
	if (ac == 2)
		all.fd = open(av[1], O_RDONLY);
	parce_input(&all);
	print_out(all.out);
	get_ways(&all, all.rooms, 1000);
	send_ants(&all);
	all.exit(&all, NULL, 1);
	return (0);
}
