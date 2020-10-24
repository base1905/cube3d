/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:53 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 15:41:51 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_initstruct(t_all *pb)
{
	int i;

	pb->line = NULL;
	pb->bmp_screenshot = 0;
	pb->screen_x = 0;
	pb->screen_y = 0;
	pb->map_height = 0;
	pb->map_width = 0;
	pb->map_string = NULL;
	pb->map_array = NULL;
	i = -1;
	while (++i < 5)
		pb->path[i] = NULL;
	pb->window = NULL;
	pb->mlx = NULL;



	pb->plr->start_x = -1;
	pb->plr->start_y = -1;
	pb->plr->dir = 0;

}


