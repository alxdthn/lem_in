/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 13:40:43 by nalexand          #+#    #+#             */
/*   Updated: 2019/07/21 19:48:09 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#define LEM_PATH "../lem-in"
#define MAP_PATH "nvalid_maps/"

char	*get_cmd_body(void)
{
	char	*cmd;
	char	*tmp;

	cmd = ft_strdup(LEM_PATH);
	tmp = ft_strjoin(cmd, " < ");
	ft_strdel(&cmd);
	cmd = tmp;
	tmp = ft_strjoin(cmd, MAP_PATH);
	ft_strdel(&cmd);
	cmd = tmp;
	return (cmd);
}

char	*get_cmd(char *cmd_body, char *line, char **val)
{
	char	*tmp;
	char	*cmd;

	cmd = ft_strjoin(cmd_body, line);
	*val = ft_strdup(cmd);
	tmp = ft_strjoin(cmd, " &> out.txt");
	ft_strdel(&cmd);
	cmd = tmp;
	tmp = ft_strjoin("valgrind --leak-check=full --log-file=\"val.txt\" ", *val);
	ft_strdel(val);
	*val = tmp;
	tmp = ft_strjoin(*val, " 2> tmp.txt");
	ft_strdel(val);
	*val = tmp;
	return (cmd);
}

static void	read_leaks(int *leaks, int *errors)
{
	int		fd;
	char	*val;
	char	*lks;
	char	*err;

	fd = open("val.txt", O_RDONLY);
	ft_read_to_str(fd, &val, 256);
	lks = ft_strstr(val, "definitely lost: ");
	err = ft_strstr(val, "ERROR SUMMARY: ");
	while (lks && *lks && !ft_isdigit(*lks))
		lks++;
	*leaks = ft_atoi(lks);
	while (err && *err && !ft_isdigit(*err))
		err++;
	*errors = ft_atoi(err);
	ft_strdel(&val);
	close(fd);
}

static void	make_test(char *cmd, char *test, char *val)
{
	int		fd;
	char	*log;
	int		leaks;
	int		errors;

	system(val);
	leaks = 0;
	errors = 0;
	read_leaks(&leaks, &errors);
	system(cmd);
	fd = open("out.txt", O_RDONLY);
	ft_read_to_str(fd, &log, 256);
	close(fd);
	ft_printf("[%s] leaks: %d errors: %d\n", test, leaks, errors);
	if (!ft_strequ("Error\n", log))
		ft_printf("\033[31m[ KO ]\033[0m\n");
	else
		ft_printf("\033[32m[ OK ]\033[0m\n");
	ft_strdel(&log);
}

int		main(void)
{
	int		fd;
	char	*line;
	char	*cmd;
	char	*cmd_body;
	char	*val;

	system("ls nvalid_maps > map_list.txt");
	if ((fd = open("map_list.txt", O_RDONLY)) < 3)
		exit(EXIT_FAILURE);
	cmd_body = get_cmd_body();
	while (get_next_line(fd, &line))
	{
		cmd = get_cmd(cmd_body, line, &val);
		make_test(cmd, line, val);
		ft_strdel(&line);
		ft_strdel(&cmd);
		ft_strdel(&val);
	}
	close(fd);
	ft_strdel(&cmd_body);
}
