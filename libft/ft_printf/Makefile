# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/11 16:58:18 by nalexand          #+#    #+#              #
#    Updated: 2019/07/19 20:35:00 by nalexand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
C_FLAGS = -Wall -Werror -Wextra
HEADER = -I includes -I ../includes

SRC_DIR = src/
OBJ_DIR = obj/

SRC =	ft_printf.c \
		pf_ltoa_base.c \
		pf_get_params.c \
		pf_parce.c \
		pf_set_params.c \
		pf_set_zero.c \
		pf_set_task.c \
		pf_set_arg_digit.c \
		pf_solve_digit.c \
		pf_solve_pcsn.c \
		pf_solve_float.c \
		pf_solve_bits.c \
		pf_get_ldbl.c \
		pf_get_float_mod.c \
		pf_get_float_div.c \
		pf_add_lnbr.c \
		pf_multi_lnbr.c \
		pf_lnbr.c \
		pf_unicode.c \
		pf_solve_unicode.c \
		pf_colors.c \
		pf_fun.c \
		pf_debug.c

SRCS = $(addprefix $(SRC_DIR), $(SRC))

OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	ar rc $@ $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	gcc $(C_FLAGS) -c $< -o $@ $(HEADER)

$(OBJ_DIR):
	mkdir $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all