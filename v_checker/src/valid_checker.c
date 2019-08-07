/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 13:40:43 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/07 20:21:01 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_checker.h"

static void	read_leaks(int *leaks, int *errors)
{
	int		fd;
	char	*val;
	char	*lks;
	char	*err;

	fd = open("tmp/val.txt", O_RDONLY);
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

void	make_test(t_all *all)
{
	int		fd;
	char	*log;
	int		leaks;
	int		errors;

	system(all->val_cmd);
	system(all->cmd);
	leaks = 0;
	errors = 0;
	read_leaks(&leaks, &errors);
	fd = open("tmp/out.txt", O_RDONLY);
	ft_read_to_str(fd, &log, 256);
	close(fd);
	ft_printf("[%s] leaks: %d errors: %d\n", all->line, leaks, errors);
	if (log)
		ft_printf("%s\033[32m[ OK ]\033[0m\n", log);
	else
		ft_printf("\033[31m[ KO ]\033[0m\n");
	ft_strdel(&log);
}

void	get_ini(t_all *all)
{
	int		fd;
	char	*tmp;
	size_t	i;

	fd = open("v_checker.ini", O_RDONLY);
	get_next_line(fd, &all->ini);
	all->cmd_body = ft_strchr(ft_strstr(all->ini, "EXAMPLE"), ' ') + 1;
	all->val_body = ft_strjoin("valgrind --leak-check=full --log-file=\"tmp/val.txt\" ", all->cmd_body);
	tmp = ft_strstr(all->cmd_body, "invalid_input");
	all->map_list = ft_strndup(tmp, ft_strclen(tmp, ' '));
	tmp = ft_strjoin("ls ", all->map_list);
	ft_strdel(&all->map_list);
	all->map_list = tmp;
	tmp = ft_strjoin(all->map_list, " > tmp/map_list.txt");
	ft_strdel(&all->map_list);
	all->map_list = tmp;
	close(fd);
}

void	clear_all(t_all *all)
{
	ft_strdel(&all->ini);
	ft_strdel(&all->val_body);
	ft_strdel(&all->map_list);
}

void	get_cmds(t_all *all)
{
	char	*tmp;

	all->cmd = ft_strjoin(all->cmd_body, all->line);
	tmp = ft_strjoin(all->cmd, " &> tmp/out.txt");
	ft_strdel(&all->cmd);
	all->cmd = tmp;
	all->val_cmd = ft_strjoin(all->val_body, all->line);
	tmp = ft_strjoin(all->val_cmd, " &> tmp/tmp.txt");
	ft_strdel(&all->val_cmd);
	all->val_cmd = tmp;
}

int		main(void)
{
	int		fd;
	t_all	all;

	ft_bzero(&all, sizeof(t_all));
	get_ini(&all);
	system(all.map_list);
	fd = open("tmp/map_list.txt", O_RDONLY);
	while (get_next_line(fd, &all.line) > 0)
	{
		get_cmds(&all);
		make_test(&all);
		ft_strdel(&all.line);
		ft_strdel(&all.cmd);
	}
	clear_all(&all);
	close(fd);
}
