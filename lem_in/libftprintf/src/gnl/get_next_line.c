/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 22:19:55 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/31 07:05:46 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		init_new_fd(t_gnl *gnl)
{
	t_fd	new_fd;
	t_list	*node;
	t_list	*tmp;

	tmp = gnl->fd_lst;
	while (tmp)
	{
		if (((t_fd *)tmp->content)->fd == gnl->fd)
		{
			gnl->cur_fd = (t_fd **)&tmp->content;
			return (0);
		}
		tmp = tmp->next;
	}
	ft_bzero(&new_fd, sizeof(t_fd));
	new_fd.fd = gnl->fd;
	new_fd.buf = NULL;
	if (!(node = ft_lstnew(&new_fd, sizeof(t_fd))))
		return (-1);
	ft_lstadd(&gnl->fd_lst, node);
	gnl->cur_fd = (t_fd **)&node->content;
	return (0);
}

static void		write_from_list(t_gnl *gnl, char **line)
{
	t_list	*tmp;
	t_list	*tmp2;
	size_t	ofset;

	ofset = gnl->lst_ofset;
	if ((*gnl->cur_fd)->buf->next)
	{
		tmp = (*gnl->cur_fd)->buf->next;
		while (tmp)
		{
			ofset -= tmp->content_size;
			tmp2 = tmp->next;
			ft_memcpy(*line + ofset, tmp->content, tmp->content_size);
			free(tmp->content);
			free(tmp);
			tmp = tmp2;
		}
		(*gnl->cur_fd)->buf->next = NULL;
	}
	else
		gnl->lst_ofset = 0;
}

static void		write_line(t_gnl *gnl, char **line)
{
	write_from_list(gnl, line);
	ft_memcpy(*line + gnl->lst_ofset, CONT, gnl->node_ofset);
	if (gnl->tmp_ptr && SIZE - gnl->node_ofset - 1)
	{
		gnl->tmp_ptr = ft_memdup(gnl->tmp_ptr + 1, SIZE - gnl->node_ofset - 1);
		ft_memdel(&CONT);
		CONT = gnl->tmp_ptr;
		SIZE -= gnl->node_ofset + 1;
	}
	else
		ft_lstdelone(&(*gnl->cur_fd)->buf, ft_lstclear);
}

static ssize_t	get_new_line(t_gnl *gnl, char **line)
{
	t_list	*new_buf;

	while (!(*gnl->cur_fd)->buf
	|| !(gnl->tmp_ptr = ft_memchr(CONT, '\n', SIZE)))
	{
		if (!(gnl->read_ret = read(gnl->fd, gnl->buf, BUFF_SIZE)))
			break ;
		if ((*gnl->cur_fd)->buf)
			gnl->lst_ofset += (*gnl->cur_fd)->buf->content_size;
		if (!(new_buf = ft_lstnew(gnl->buf, gnl->read_ret)))
			return (gnl->ret = -1);
		ft_lstadd(&(*gnl->cur_fd)->buf, new_buf);
	}
	if (gnl->lst_ofset < 0)
		gnl->lst_ofset = 0;
	if (!(*gnl->cur_fd)->buf && !gnl->read_ret)
		return (gnl->ret = 0);
	gnl->node_ofset = (gnl->tmp_ptr)
	? (ssize_t)gnl->tmp_ptr - (ssize_t)CONT : SIZE;
	gnl->ret = (gnl->tmp_ptr || !gnl->read_ret)
	? gnl->node_ofset + gnl->lst_ofset + 1 : gnl->node_ofset + 1;
	if (!(*line = ft_memalloc(gnl->ret)))
		return (gnl->ret = -1);
	write_line(gnl, line);
	return (0);
}

ssize_t			get_next_line(const int fd, char **line)
{
	static t_gnl	gnl;
	char			tmp_buf[0];

	if (fd < 0 || line == NULL || (read(fd, tmp_buf, 0)) < 0)
		return (-1);
	gnl.lst_ofset = 0;
	gnl.node_ofset = 0;
	gnl.read_ret = 0;
	gnl.ret = 0;
	gnl.fd = fd;
	*line = NULL;
	if (init_new_fd(&gnl) == -1)
	{
		ft_lstdel(&gnl.fd_lst, fd_lst_clear);
		return (-1);
	}
	get_new_line(&gnl, line);
	if (gnl.ret == -1)
		ft_lstdel(&gnl.fd_lst, fd_lst_clear);
	if (!(*gnl.cur_fd)->buf && !gnl.read_ret)
		clear_fd_node(&gnl);
	if (gnl.ret > 0)
		gnl.ret = 1;
	return (gnl.ret);
}
