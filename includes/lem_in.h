/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:22:42 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/25 21:18:46 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define LEM_IN 42
# define VISU_HEX 21
# define ERROR "Error"
# define START 1
# define END 2
# define ABS(x) ((x) > 0 ? (x) : -(x))
# define WAY_COLOR 0xffffff
# define ROOM_FIL_COLOR 0x000000
# define ROOM_BORDER 0xffffff
# define START_ROOM_COLOR 0xfc03f0
# define END_ROOM_COLOR 0x7b09e6
# define BACKGROUND_COLOR 0
# include "libft.h"
# include "ft_printf.h"
# include "mlx_keys.h"
# include <mlx.h>

typedef struct	s_line_params
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			delta_x;
	int			delta_y;
	int			dir_x;
	int			dir_y;
}				t_line_params;

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
	char		is_print;
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
	t_img		img;
	void		*ptr;
	void		*win;
	int			width;
	int			height;
	int			size;
	int			pixel_size;
	int			radius;
	int			color;
	int			min_x;
	int			max_x;
	int			min_y;
	int			max_y;
	int			map_size;
	int			map_position_x;
	int			map_position_y;
	int			size_x_sum;
	int			size_y_sum;
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
void			draw_line(t_all *all, t_line_params *params);
void			draw_circle(t_all *all, t_line_params *params);

#endif