# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/29 16:28:19 by nalexand          #+#    #+#              #
#    Updated: 2019/07/21 18:29:02 by nalexand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM = lem-in

COM_LIB = common.a
LEM_LIB = lem-in.a
LIBFT = libft/libft.a
FTPRINTF = libft/ft_printf/libftprintf.a

MLX_LIB = -L /usr/local/lib/ -lmlx
MLX_HEAD = -I /usr/local/include
FRAMEWORK = -framework OpenGL -framework AppKit

C_FLAGS = -g
HEADER = -I includes -I libft/includes -I libft/ft_printf/includes

SRC_DIR = src/
OBJ_DIR = obj/
COM_DIR = common/
LEM_DIR = lem-in/

COM_SRC = 	parce_map.c \
			get_ants.c \
			get_sharp.c \
			get_room.c \
			get_door.c \
			find_room.c \
			debug.c

LEM_SRC =	lem_in.c \
			lem_in_clear_exit.c \

COM_OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(COM_SRC)))
LEM_OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(LEM_SRC)))


all: $(LEM)

$(LEM): $(LIBFT) $(FTPRINTF) $(COM_LIB) $(LEM_LIB)
	gcc $(C_FLAGS) -o $@ $(COM_LIB) $(LEM_LIB) $(LIBFT) $(FTPRINTF)

$(LIBFT):
	make -C libft/
$(FTPRINTF):
	make -C libft/ft_printf/

$(COM_LIB): $(COM_OBJ) 
	@ar rc $@ $^
$(LEM_LIB): $(LEM_OBJ) 
	@ar rc $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)$(COM_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	gcc $(C_FLAGS) -c $< -o $@ $(HEADER)
$(OBJ_DIR)%.o: $(SRC_DIR)$(LEM_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	gcc $(C_FLAGS) -c $< -o $@ $(HEADER)

clean:
	rm -f $(COM_LIB)
	rm -f $(LEM_LIB)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(LEM)
	rm -rf *.dSYM
fclean_all: fclean
	make -C libft/ fclean
	make -C libft/ft_printf fclean
re: fclean all
re_all: re
	make -C libft/ re
	make -C libft/ft_printf re	
relib:
	make -C libft/ re
	make -C libft/ft_printf re
