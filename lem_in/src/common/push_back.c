/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 21:11:45 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/29 21:12:02 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	push_back(t_list **lst, t_list *node, t_list **head)
{
	if (*lst)
	{
		(*lst)->next = node;
		(*lst) = (*lst)->next;
	}
	else
	{
		(*lst) = node;
		*head = *lst;
	}
}
