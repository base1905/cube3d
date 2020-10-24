/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:53 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 15:41:51 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_struct(t_all *pb)
{
	int i;

	free (pb->line);
	free (pb->map_string);

	i = -1;
	while (++i < 5)
		free(pb->path[i]);

}

int		ft_exit_error(t_all *pb)
{
	free_struct(pb);
	exit(1);
	return (1);
}