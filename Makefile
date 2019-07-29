# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/29 16:28:19 by nalexand          #+#    #+#              #
#    Updated: 2019/07/29 06:33:50 by nalexand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEAD = ./includes/lem_in.h
LEM = lem-in
VIS = visu-hex

COM_LIB = common.a
LEM_LIB = lem-in.a
VIS_LIB = visu-hex.a
LIBFT = libftprintf/libftprintf.a

MLX_LIB = -L /usr/local/lib/ -lmlx
MLX_HEAD = -I /usr/local/include
FRAMEWORK = -framework OpenGL -framework AppKit

C_FLAGS = -g
HEADER = -I includes -I libftprintf/includes

SRC_DIR = src/
OBJ_DIR = obj/
COM_DIR = common/
LEM_DIR = lem-in/
VIS_DIR = visu-hex/

COM_SRC = 	parce_map.c \
			get_ants.c \
			get_sharp.c \
			get_room.c \
			get_door.c \
			find_functions.c \
			debug.c
LEM_SRC =	lem_in.c \
			lem_in_clear_exit.c \
			bfs.c \
			queue.c \
			ways.c \
			solver.c \
			create_str.c
VIS_SRC =	visu_hex.c \
			visu_hex_clear_exit.c \
			visualisation_init.c \
			parce_ants.c \
			key_handle.c \
			render.c \
			render_map.c \
			render_ants.c \
			render_info.c \
			put_functions.c \
			draw_functions.c \
			gradient.c

COM_OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(COM_SRC)))
LEM_OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(LEM_SRC)))
VIS_OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(VIS_SRC)))

all: $(LEM) $(VIS)

$(LEM): $(LIBFT) $(COM_LIB) $(LEM_LIB)
	gcc $(C_FLAGS) -o $@ $(COM_LIB) $(LEM_LIB) $(LIBFT)
$(VIS): $(LIBFT) $(COM_LIB) $(VIS_LIB)
	gcc $(C_FLAGS) -o $@ $(COM_LIB) $(VIS_LIB) $(LIBFT) $(MLX_LIB) $(MLX_HEAD) $(FRAMEWORK)

$(LIBFT):
	make -C libftprintf/

$(COM_LIB): $(COM_OBJ) 
	@ar rc $@ $^
$(LEM_LIB): $(LEM_OBJ) 
	@ar rc $@ $^
$(VIS_LIB): $(VIS_OBJ) 
	@ar rc $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)$(COM_DIR)%.c $(HEAD)
	@mkdir -p $(OBJ_DIR)
	gcc $(C_FLAGS) -c $< -o $@ $(HEADER)
$(OBJ_DIR)%.o: $(SRC_DIR)$(LEM_DIR)%.c $(HEAD)
	@mkdir -p $(OBJ_DIR)
	gcc $(C_FLAGS) -c $< -o $@ $(HEADER)
$(OBJ_DIR)%.o: $(SRC_DIR)$(VIS_DIR)%.c $(HEAD)
	@mkdir -p $(OBJ_DIR)
	gcc $(C_FLAGS) -c $< -o $@ $(HEADER)

clean:
	rm -f $(COM_LIB)
	rm -f $(LEM_LIB)
	rm -f $(VIS_LIB)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(LEM)
	rm -f $(VIS)
	rm -rf *.dSYM

fclean_all: fclean
	make -C libftprintf/ fclean

re: fclean all

relib:
	make -C libftprintf/ re
