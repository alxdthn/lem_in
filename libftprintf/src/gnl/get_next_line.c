/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 16:05:42 by vsanta            #+#    #+#             */
/*   Updated: 2019/07/12 20:59:07 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int		ft_to_line(char **line, char **tmp, int ret)
{
	char	*tmp_b;
	int		n_ind;

	n_ind = 0;
	while ((*tmp)[n_ind] != '\0' && (*tmp)[n_ind] != '\n')
		n_ind++;
	if ((*tmp)[0] == '\0' && ret == 0)
	{
		ft_strdel(tmp);
		return (0);
	}
	if ((*line = ft_strsub(*tmp, 0, n_ind)) == NULL)
		return (-1);
	if ((tmp_b = ft_strsub(*tmp, n_ind + 1, ft_strlen(*tmp) - n_ind)) == NULL)
		return (-1);
	free(*tmp);
	*tmp = tmp_b;
	return (1);
}

static	int		ft_free_tmpfd(char **tmp)
{
	free(*tmp);
	return (-1);
}

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static	char	*tmp[MAX_FD + 1];
	char			*tmp_b;
	int				ret;

	if (line == NULL || fd < 0 || fd > MAX_FD)
		return (-1);
	if (tmp[fd] == NULL)
		if ((tmp[fd] = ft_strnew(0)) == NULL)
			return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if ((tmp_b = ft_strjoin(tmp[fd], buf)) == NULL)
			return (ft_free_tmpfd(&tmp[fd]));
		free(tmp[fd]);
		tmp[fd] = tmp_b;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	return (ft_to_line(line, &tmp[fd], ret));
}
