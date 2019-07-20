# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/29 16:28:19 by nalexand          #+#    #+#              #
#    Updated: 2019/07/20 18:12:51 by nalexand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM = lem-in

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
LEM_DIR = lem-in/

LEM_SRC =	lem_in.c \
			lem_in_clear_exit.c \
			parce_map.c

LEM_OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(LEM_SRC)))

all: $(LEM)

$(LEM): $(LIBFT) $(FTPRINTF) $(LEM_LIB)
	gcc $(C_FLAGS) -o $@ $(LEM_LIB) $(LIBFT) $(FTPRINTF)

$(LIBFT):
	make -C libft/
$(FTPRINTF):
	make -C libft/ft_printf/

$(LEM_LIB): $(LEM_OBJ) 
	@ar rc $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)$(LEM_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	gcc $(C_FLAGS) -c $< -o $@ $(HEADER)

clean:
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
