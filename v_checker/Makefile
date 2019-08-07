# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/21 13:47:17 by nalexand          #+#    #+#              #
#    Updated: 2019/08/07 20:22:09 by nalexand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_FLAGS = -g
NAME = run_test
LIBFT = ../libftprintf/libftprintf.a
SRC_DIR = src/
OBJ_DIR = obj/
HEADER = -I ../libftprintf/includes -I includes
HEAD = includes/v_checker.h
SRC = valid_checker.c
OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	gcc $(C_FLAGS) -o $(NAME) $^ $(LIBFT)
	@mkdir -p tmp

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEAD)
	@mkdir -p $(OBJ_DIR)
	gcc $(C_FLAGS) -c $< -o $@ $(HEADER)

clean:
	rm -rf *.dSYM
	rm -f *.txt
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)

re: clean all