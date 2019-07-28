/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:21:11 by nalexand          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/07/28 14:32:58 by skrystin         ###   ########.fr       */
=======
/*   Updated: 2019/07/28 06:20:49 by nalexand         ###   ########.fr       */
>>>>>>> 46f4315e1285062d7dcfd35a48828cd5245d9015
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_out(t_list *list)
{
	if (list->next)
		print_out(list->next);
	ft_putendl(list->content);
}

int			main(void)
{
	t_all	all;

	ft_bzero(&all, sizeof(t_all));
	all.prog = LEM_IN;
	all.exit = &lem_in_clear_exit;
	parce_input(&all);
<<<<<<< HEAD
	ft_create_mas(&all, all.rooms);
	ft_bfs(&all, all.rooms);
=======
//	ft_bfs(&all, all.rooms);
//	print(&all);
>>>>>>> 46f4315e1285062d7dcfd35a48828cd5245d9015
	print_out(all.out);
	//ft_printf("\n");
	//ft_printf("L1-2 L2-3\nL1-7 L2-5\nL1-2 L2-2\nL1-7 L2-4\nL1-6 L2-0\nL1-5\nL1-2\nL1-4\nL1-0\n"); //for model_1
	//ft_printf("L1-1 L2-3\nL1-4 L2-4 L3-1 L4-3\nL3-4 L4-4\n"); //for 2-2
	all.exit(&all, NULL, 1);
	return (0);
}
