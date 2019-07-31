/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 16:05:48 by vsanta            #+#    #+#             */
/*   Updated: 2019/07/31 03:24:50 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# define BUFF_SIZE 1000000
# define MAX_FD 4864

int	get_next_line(const int fd, char **line);

#endif
