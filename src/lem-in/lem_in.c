/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:21:11 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/20 21:35:40 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_rooms_list(t_list *tmp)
{
	char	*name;
	int		x;
	int		y;

	if (tmp->next)
		print_rooms_list(tmp->next);
	name = ((t_room *)tmp->content)->name;
	x = ((t_room *)tmp->content)->x;
	y = ((t_room *)tmp->content)->y;
	if (((t_room *)tmp->content)->type == START)
		ft_printf("|%{gre}10s|%{gre}7d|%{gre}7d|\n", name, x, y);
	else if (((t_room *)tmp->content)->type == END)
		ft_printf("|%{yel}10s|%{yel}7d|%{yel}7d|\n", name, x, y);
	else
		ft_printf("|%10s|%7d|%7d|\n", name, x, y);
}

static void print_rooms(t_list *tmp)
{
	ft_printf("|___name___|___x___|___y___|\n");
	print_rooms_list(tmp);
	ft_printf("|__________|_______|_______|\n");
}

int		main(void)
{
	t_all	all;

	ft_bzero(&all, sizeof(t_all));
	all.prog = LEM_IN;
	all.exit = &lem_in_clear_exit;
	parce_map(&all);
	print_rooms(all.rooms);
	all.exit(&all, NULL, 1);
	return (0);
}
