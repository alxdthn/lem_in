/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 02:18:38 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/29 23:39:34 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	write_from_list(t_gnl *gnl)
{
	t_list	**tmp;
	t_list	**tmp2;
	size_t	ofset;

	ofset = gnl->lst_ofset;
	if ((*gnl->cur_fd)->buf->next)
	{
		tmp = &(*gnl->cur_fd)->buf->next;
		while (*tmp)
		{
			ofset -= (*tmp)->content_size;
			tmp2 = &(*tmp)->next;
			ft_memcpy(*gnl->line + ofset, (*tmp)->content, (*tmp)->content_size);
			ft_lstdelone(tmp, ft_lstclear);
			*tmp = *tmp2;
		}
	}
}

void			write_line(t_gnl *gnl)
{
	char	*str_tmp;
	size_t	size;

	str_tmp = ft_memchr(CONT, '\n', SIZE);
	size = (str_tmp) ? (size_t)str_tmp - (size_t)CONT : SIZE;
	write_from_list(gnl);
	ft_memcpy(*gnl->line + gnl->lst_ofset, CONT, size);
	if (str_tmp && SIZE - size - 1)
	{
		str_tmp = ft_memdup(str_tmp + 1, SIZE - size - 1);
		ft_memdel(&CONT);
		CONT = str_tmp;
		SIZE -= size + 1;
	}
	else
		ft_lstdelone(&(*gnl->cur_fd)->buf, ft_lstclear);
}
