/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisation_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 20:07:20 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/21 21:33:51 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	read_line(t_all *all, int fd, int *res, char *str)
{
	char	*line;

	line = NULL;
	if (get_next_line(fd, &line))
	{
		if (!line)
			all->exit(all, ERROR, 2);
		if (!ft_strncmp(line, str, ft_strlen(str)))
		{
			if (ft_isint(line + ft_strlen(str)))
			{
				*res = ft_atoi(line + ft_strlen(str));
				ft_strdel(&line);
				return ;
			}
		}
	}
	if (line)
		ft_strdel(&line);
	all->exit(all, ERROR, 2);
}

static void	read_ini(t_all *all)
{
	int		fd;

	fd = open("visu-hex.ini", O_RDONLY);
	if (fd < 3)
	{
		all->mlx.width = 1000;
		all->mlx.height = 500;
	}
    else
	{
		read_line(all, fd, &all->mlx.width, "width: ");
		read_line(all, fd, &all->mlx.height, "height: ");
		if (all->mlx.width < 300 || all->mlx.height < 300
		|| all->mlx.width > 3000 || all->mlx.height > 3000)
		    all->exit(all, ERROR, 2);
	}
}

static void	mlx_init_params(t_all *all)
{
	read_ini(all);
	all->mlx.ptr = mlx_init();
	all->mlx.win = mlx_new_window(all->mlx.ptr,
	all->mlx.width, all->mlx.height, "visu-hex by nalexand");
	all->mlx.logo.ptr = mlx_xpm_file_to_image(all->mlx.ptr,
	"src/logo2.xpm", &all->mlx.logo.bpp, &all->mlx.logo.bpp);
	all->mlx.img.ptr = mlx_new_image(all->mlx.ptr, all->mlx.width, all->mlx.height);
	all->mlx.img.data = (int *)mlx_get_data_addr(all->mlx.img.ptr,
	&all->mlx.img.bpp, &all->mlx.img.size_line, &all->mlx.img.endian);
	all->mlx.img.size_line /= 4;
	all->mlx.size = all->mlx.width * all->mlx.height;
}

void		visualisation_init(t_all *all)
{
	mlx_init_params(all);
	mlx_key_hook(all->mlx.win, deal_key, all);
	//mlx_loop_hook(all->mlx.ptr, loop_hook, all);
	//mlx_hook(all->mlx.win, 2, 0, key_press, all);
}
