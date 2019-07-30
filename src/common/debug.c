/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:11:50 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/31 00:35:57 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_doors_list(t_list *tmp)
{
	if (tmp->next)
		print_doors_list(tmp->next);
	ft_printf(" %.*s,", ((t_door *)tmp->content)->room->name_len,
	((t_door *)tmp->content)->room->name);
}

static void	print_rooms_list(t_list *tmp)
{
	size_t	name_len;
	char	*name;
	int		x;
	int		y;

	if (tmp->next)
		print_rooms_list(tmp->next);
	name_len = ((t_room *)tmp->content)->name_len;
	name = ((t_room *)tmp->content)->name;
	x = ((t_room *)tmp->content)->x;
	y = ((t_room *)tmp->content)->y;
	if (((t_room *)tmp->content)->type == START)
		ft_printf("|%{blu}-25.*s|%{blu}-7d|%{blu}-7d|", name_len, name, x, y);
	else if (((t_room *)tmp->content)->type == END)
		ft_printf("|%{red}-25.*s|%{red}-7d|%{red}-7d|", name_len, name, x, y);
	else
		ft_printf("|%-25.*s|%-7d|%-7d|", name_len, name, x, y);
	if (((t_room *)tmp->content)->doors)
		print_doors_list(((t_room *)tmp->content)->doors);
	ft_putchar('\n');
}

void		print(t_all *all)
{
	ft_printf("|___________name__________|___x___|___y___|\n");
	print_rooms_list(all->rooms);
	ft_printf("|_________________________|_______|_______|\n");
	ft_printf("ants: %d\n", all->ant_count);
}

void	print_ant_path(t_list *ants, int name)
{
	while (ants && ((t_ant *)ants->content)->name != name)
		ants = ants->next;
	print_rooms_list(((t_ant *)ants->content)->path);
}

void	print_way(t_room **way, int way_number, int way_len, int way_ants)
{
	int		i;

	ft_printf("path №%d (len %d, ants %d sum %d): ", way_number, way_len, way_ants, (way_ants) ? way_len + way_ants : 0);
	i = 0;
	//while (way[i])
	//{
	//	ft_printf("%.*s", way[i]->name_len, way[i]->name);
	//	if (way[i + 1])
	//		ft_printf(" -> ");
	//	++i;
	//}
}

void	print_ways(t_all *all)
{
	t_ways	*node;

	node = all->ways;
	while (node)
	{
		print_way(node->way, node->nb, node->len, node->ants);
		node = node->next;
		ft_printf("\n");
	}
}

void	print_ants(t_all *all)
{
	t_list	*tmp_ant;

	ft_printf("\nANTS\n______________\n");
	ft_printf("_name_|_way_\n");
	tmp_ant = all->ants;
	while (tmp_ant)
	{
		ft_printf("%-6d| ", ((t_ant *)tmp_ant->content)->name);
		if (((t_ant *)tmp_ant->content)->way)
		{
			print_way(((t_ant *)tmp_ant->content)->way->way,
			((t_ant *)tmp_ant->content)->way->nb,
			((t_ant *)tmp_ant->content)->way->len,
			((t_ant *)tmp_ant->content)->way->ants);
			ft_printf("\n");
		}
		else
			ft_printf("%p\n", ((t_ant *)tmp_ant->content)->way);
		tmp_ant = tmp_ant->next;
	}
}
