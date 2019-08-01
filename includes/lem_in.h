/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:22:42 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 06:15:52 by nalexand         ###   ########.fr       */
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
# define INFO_COLOR 0x005dba
# define WAY_COLOR 0x404040
# define ROOM_BORDER WAY_COLOR
# define ROOM_NAME_COLOR INFO_COLOR
# define START_ROOM_COLOR 0xff9d00
# define END_ROOM_COLOR 0xeb4034
# define BACKGROUND_COLOR 0xFFFFFF
# define ROOM_FIL_COLOR BACKGROUND_COLOR
# define NEXT next
# define ANT ((t_ant *)ant->content)
# define LINE ((char *)lines->content)
# define ROOM ((t_room *)room->content)
# define DOOR ((t_door *)door->content)
# define ANT_WAY ((t_way *)ANT->way->content)
# define WAY ((t_way *)way->content)
# define WAY_N(name) ((t_way *)name->content)
# define WAY_P(position) ((t_way *)way->position->content)
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
	char		start;
	char		end;
	char		started;
	char		ended;
	char		rooms;
	char		ants;
}				t_switchs;

typedef struct	s_room
{
	int			nb;
	int			x;
	int			y;
	int			visit;
	size_t		name_len;
	char		*name;
	int			ant_count;
	int			way_nb;
	t_list 		*doors;
	char		type;
	char		visit_early;
	char		go_away;
}				t_room;

typedef	struct		s_way
{
	t_room			**path;
	int				len;
	int				ants;
	int				nb;
}					t_way;

typedef struct	s_ant
{
	t_list		*path;
	t_list		*way;
	int			position;
	double		x1;
	double		y1;
	double		x2;
	double		y2;
	double		delta_x;
	double		delta_y;
	double		speed_x;
	double		speed_y;
	double		start_point;
	double		end_point;
	double		cur_point;
	int			dir_x;
	int			dir_y;
	int			name;
	char		is_counted;
	char		in_place;
}				t_ant;

typedef struct	s_door
{
	t_room		*room;
	char		is_close;
	char		is_print;
	char		is_neg;
}				t_door;

typedef struct		s_que
{
	t_room			*room;
	struct s_que	*next;
}					t_que;

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

typedef struct	s_flags
{
	char		working;
	char		names;
	char		no_visu;
	char		print_way_info;
	char		print_way_info_path;
	char		print_err;
	char		normalize_map;
	char		print_info;
	char		print_rooms;
	char		print_iterations;
}				t_flags;

typedef struct	s_mlx
{
	t_img		logo;
	t_img		map;
	t_img		ants;
	t_flags		flags;
	
	void		*ptr;
	void		*win;
	char		*info_iter;
	char		*info_ant_in_end;
	char		*info_count_of_ants;
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
	int			min_path_size;
}				t_mlx;

typedef struct	s_all
{
	t_mlx		mlx;
	t_tmp		tmp;
	t_list		*input;
	t_list		*input_head;
	t_list		*out;
	t_list		*out_head;
	t_list		*ants;
	t_list		*ants_head;
	t_list		*rooms;
	t_list		*ways;
	t_list		*dependent_ways;
	t_room		**mas_rom;
	t_room		*start_room;
	t_room		*end_room;
	t_ant		***iterations;
	t_switchs	switchs;
	int			ant_count;
	int			room_count;
	int			way_count;
	int			fd;
	char		prog;
	char		debug;
	void		(*exit)(struct s_all *, char *, int);
}				t_all;
/*
** common
*/
void			parce_input(t_all *all);
void			push_back(t_list **lst, t_list *node, t_list **head);
void			clear_room_visit(t_room **mas_rom);
t_room			*find_room_in_doors_list_by_nb(t_list *rooms, int nb);
t_room			*find_room_by_name(t_list *rooms, char *name);
t_door			*find_door_by_room_nb(t_room *room, int nb);
t_list			*find_ant_by_name(t_list *ants, int name);
t_list			*find_way_by_nb(t_list *way, int nb);
void			get_ants(t_all *all);
void			get_sharp(t_all *all);
void			get_room(t_all *all);
void			get_door(t_all *all);
void			clear_room(void *, size_t size);
void			clear_ant(void *, size_t size);
void			clear_way(void *, size_t size);
void			error_handle(t_all *all, char *message, int fd);
/*
** visu-hex
*/
void			visu_hex_clear_exit(t_all *all, char *message, int fd);
void			parce_ants(t_all *all);
void			parce_flags(t_all *all, int ac, char **av);
void			normalize_rooms(t_all *all);
void			get_min_max(t_all *all);
void			normalize(t_all *all);
void			init_sizes(t_all *all);
void			reset_crds(t_all *all);
void			count_ants_paths(t_all *all);
void			visualisation_init(t_all *all);
int				init_new_way(t_all *all, t_list *ant, int counter);
void			init_map(t_all *all);
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
int				get_gradient(double start, double end, double cur);
char			*get_line(t_list *lines, int line_number);
void			validate_iterations(t_all *all);
void			validate_ways(t_all *all);
void			draw_line(t_img *img, t_line_params *params);
void			draw_circle(t_img *img, t_line_params *params);
void			draw_pixel_circle(t_img *img, t_line_params *params);
void			draw_point(t_img *img, int x, int y);
void			put_usage(void);
/*
** lem-in
*/
void			lem_in_clear_exit(t_all *all, char *message, int fd);
void        	get_ways(t_all *all, t_list *begin);
void			send_ants(t_all *all);
int				bfs(t_all *all, t_list *begin);
void			q_push_back(t_room *room, t_que **q, t_all *all);
void			del_first(t_que **q);
void			create_mas(t_all *all, t_list *begin);
void			create_way(t_all *all, int i, int end);
void			create_str(t_all *all, t_list *way, int ant, int name_an);
int				is_independent_ways(t_all *all, t_room **room, int i);
void			clean_room_open_ways(t_all *all, t_room **room, t_list *second, int i);
void			delete_ways(t_all *all, int i);
void			choose_ways(t_all *all, int ant, t_list *indep, t_list *dep);
int				distribute_ants_to_ways(t_all *all, t_list *way, t_list *begin, int i);
/*
** debug
*/
void 			print(t_all *all);
void			print_ants(t_all *all);
void			print_ant_path(t_list *ant, int name);
void			print_way(t_list *way, char print_path);
void			print_ways(t_all *all, char print_path);
void			print_iterations(t_all *all);
void			print_info(t_all *all);

#endif