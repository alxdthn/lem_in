/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_usage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 06:06:43 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/02 12:46:48 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	put_usage(void)
{
	ft_putstr("usage:\t./visu-hex [-vwWbarip] [stdin/file]\n");
	ft_putstr("\t-v no visualisation\n");
	ft_putstr("\t-w detect and show ways information\n");
	ft_putstr("\t-W detect and show ways information width path\n");
	ft_putstr("\t-b show info about visualization\n");
	ft_putstr("\t-a show info about rooms\n");
	ft_putstr("\t-r show error if ants go in one room one time\n");
	ft_putstr("\t-i show error if ant go in one iteration two times\n");
	ft_putstr("\t-p show error if path merged\n");
}
