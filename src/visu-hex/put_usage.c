/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_usage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 06:06:43 by nalexand          #+#    #+#             */
/*   Updated: 2019/08/01 18:22:24 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	put_usage(void)
{
	ft_putstr("usage:\t./visu-hex [-vwWemiat] [stdin/file]\n");
	ft_putstr("\t-v no visualisation\n");
	ft_putstr("\t-w detect and show ways information\n");
	ft_putstr("\t-W detect and show ways information width path\n");
	ft_putstr("\t-e abort program if paths merge or some ants in one\n");
	ft_putstr("\t-m with -e print merged ways\n");
	ft_putstr("\t-i show info about visualization\n");
	ft_putstr("\t-a show info about rooms\n");
	ft_putstr("\t-t print iterations\n");
}
