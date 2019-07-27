/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:22:42 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/27 23:34:17 by nalexand         ###   ########.fr       */
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
# define ANT_COLOR 0x34abeb
# define WAY_COLOR 0xffffff
# define ROOM_FIL_COLOR 0x000000
# define ROOM_BORDER 0xffffff
# define START_ROOM_COLOR 0x34abeb
# define END_ROOM_COLOR 0xeb4034
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
	char		rooms : 1;
	char		ants : 3;
}				t_switchs;

typedef struct	s_room
{
	int			nb;
	int			x;
	int			y;
	size_t		name_len;
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

typedef struct	s_ant
{
	t_list		*path;
	double		x1;
	double		y1;
	double		x2;
	double		y2;
	double		delta_x;
	double		delta_y;
	double		speed_x;
	double		speed_y;
	int			dir_x;
	int			dir_y;
	int			name;
	char		is_counted;
	char		in_place;
}				t_ant;

typedef struct	s_tmp
{
	char		*line;
}				t_tmp;

typedef struct  s_img
{
	void		*ptr;
	int			*data;
	int			bpp;
	int			size_line;
	int			endian;
	int			pixel_size;
	int			pixel_color;
	int			size;
}				t_img;

typedef struct	s_mlx
{
	t_img		logo;
	t_img		map;
	t_img		ants;
	t_room		*start_room;
	void		*ptr;
	void		*win;
	char		*info_iter;
	char		*info_ant_in_end;
	int			width;
	int			height;
	int			size;
	int			pixel_size;
	int			room_radius;
	int			ant_radius;
	int			color;
	int			min_x;
	int			max_x;
	int			min_y;
	int			max_y;
	int			map_size;
	int			map_position_x;
	int			map_position_y;
	int			cur_iter;
	int			speed;
	int			ants_in_end;
	char		working;
}				t_mlx;

typedef struct	s_all
{
	t_mlx		mlx;
	t_tmp		tmp;
	t_list		*rooms;
	t_list		*ants;
	t_switchs	switchs;
	t_list		*out;
	t_ant		***iterations;
	int			ant_count;
	char		prog;
	void		(*exit)(struct s_all *, char *, int);
}				t_all;

void			lem_in_clear_exit(t_all *all, char *message, int fd);
void			visu_hex_clear_exit(t_all *all, char *message, int fd);
void			parce_input(t_all *all);

t_room			*find_room_by_name(t_list *rooms, char *name);
t_door			*find_door_by_room_nb(t_room *room, int nb);
t_ant			*find_ant_by_name(t_list *ants, int name);
void			get_ants(t_all *all);
void			get_sharp(t_all *all);
void			get_room(t_all *all);
void			get_door(t_all *all);

void 			print(t_all *all);
void			print_ants_list(t_list *ants);
void			print_ant_path(t_list *ants, int name);

void			parce_ants(t_all *all);
void			visualisation_init(t_all *all);
int				loop_hook(t_all *all);
int				deal_key(int key, t_all *all);

void			render(t_all *all);
void			render_map(t_all *all);
void			render_ants(t_all *all);
void			render_info(t_all *all);
void			put_logo(t_all *all);
void			put_map(t_all *all);
void			put_ants(t_all *all);
void			put_info(t_all *all);
void			put_names(t_all *all);

void			draw_line(t_img *img, t_line_params *params);
void			draw_circle(t_img *img, t_line_params *params);
void			draw_pixel_circle(t_img *img, t_line_params *params);
void			draw_point(t_img *img, int x, int y);

#endif