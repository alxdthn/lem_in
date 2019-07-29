/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 22:19:55 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/30 00:02:12 by nalexand         ###   ########.fr       */
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

static ssize_t	extract_line(t_gnl *gnl)
{
	t_list	*tmp;
	char	*tmp_str;

	gnl->lst_ofset = 0;
	if ((*gnl->cur_fd)->buf->next)
	{
		tmp = (*gnl->cur_fd)->buf->next;
		while (tmp)
		{
			gnl->lst_ofset += tmp->content_size;
			tmp = tmp->next;
		}
	}
	tmp_str = ft_memchr(CONT, '\n', SIZE);
	gnl->node_ofset = (tmp_str) ? (ssize_t)tmp_str - (ssize_t)CONT : SIZE;
	gnl->ret = gnl->node_ofset + gnl->lst_ofset + 1;
	if (!(*gnl->line = ft_strnew(gnl->ret - 1)))
		return (gnl->ret = -1);
	write_line(gnl);
	return (0);
}

static ssize_t	get_new_line(t_gnl *gnl)
{
	t_list	*new_buf;

	while (!(*gnl->cur_fd)->buf || !(ft_memchr(CONT, '\n', SIZE)))
	{
		if (!(gnl->read_ret = read(gnl->fd, gnl->buf, BUFF_SIZE)))
			break ;
		if (!(new_buf = ft_lstnew(gnl->buf, gnl->read_ret)))
			return (gnl->ret = -1);
		ft_lstadd(&(*gnl->cur_fd)->buf, new_buf);
	}
	if (!(*gnl->cur_fd)->buf && !gnl->read_ret)
		return (gnl->ret = 0);
	extract_line(gnl);
	return (0);
}

ssize_t			get_next_line(const int fd, char **line)
{
	static t_gnl	gnl;
	char			tmp_buf[0];

	if (fd < 0 || line == NULL
	|| (gnl.read_ret = read(fd, tmp_buf, 0)) < 0)
		return (-1);
	gnl.ret = 0;
	gnl.fd = fd;
	gnl.line = line;
	if (init_new_fd(&gnl) == -1)
	{
		ft_lstdel(&gnl.fd_lst, fd_lst_clear);
		return (-1);
	}
	get_new_line(&gnl);
	if (gnl.ret == -1)
		ft_lstdel(&gnl.fd_lst, fd_lst_clear);
	if (!(*gnl.cur_fd)->buf && !gnl.read_ret)
		clear_fd_node(&gnl);
	if (gnl.ret > 0)
		gnl.ret = 1;
	return (gnl.ret);
}
