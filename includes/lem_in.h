/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:22:42 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/21 20:21:17 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define LEM_IN 42
# define VISU_HEX 21
# define ERROR "Error"
# define START 1
# define END 2
# include "libft.h"
# include "ft_printf.h"
# include "mlx_keys.h"
# include <mlx.h>

typedef struct	s_switchs
{
	char		start : 1;
	char		end : 1;
	char		started : 1;
	char		ended : 1;
	char		ants : 1;
}				t_switchs;


typedef struct	s_room
{
	int			x;
	int			y;
	char		*name;
	t_list 		*doors;
	char		type;
}				t_room;

typedef struct	s_door
{
	t_room		*room;
	char		is_close;
}				t_door;

typedef struct	s_tmp
{
	char		*line;
	char		*name;
}				t_tmp;

typedef struct  s_img
{
	void		*ptr;
	int			*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct	s_mlx
{
	t_img		logo;
	void		*ptr;
	void		*win;
	int			width;
	int			height;
}				t_mlx;

typedef struct	s_all
{
	t_mlx		mlx;
	t_tmp		tmp;
	t_list		*rooms;
	t_switchs	switchs;
	t_list		*out;
	int			ants;
	char		prog;
	void		(*exit)(struct s_all *, char *, int);
}				t_all;

void			lem_in_clear_exit(t_all *all, char *message, int fd);
void			visu_hex_clear_exit(t_all *all, char *message, int fd);
void			parce_map(t_all *all);

t_room			*find_room(t_all *all, char *name);
void			get_ants(t_all *all);
void			get_sharp(t_all *all);
void			get_room(t_all *all);
void			get_door(t_all *all);

void 			print(t_all *all);

void			visualisation_init(t_all *all);
int				deal_key(int key, t_all *all);
void			render(t_all *all);

#endif