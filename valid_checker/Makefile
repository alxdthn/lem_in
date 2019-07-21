# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/21 13:47:17 by nalexand          #+#    #+#              #
#    Updated: 2019/07/21 19:23:33 by nalexand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = v_checker

LIBFT = ../libft/
LIBFTPRINTF = ../libft/ft_printf/

SRC = valid_checker.c

HEADER = -I $(LIBFT)includes -I $(LIBFTPRINTF)includes

all: $(NAME)

$(NAME):
	gcc -g $(SRC) -o $(NAME) $(LIBFT)libft.a $(LIBFTPRINTF)libftprintf.a $(HEADER)

clean:
	rm -f $(NAME)

re: clean all