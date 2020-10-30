/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_spr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:53 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 15:41:51 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	find_sprites(t_all *pb)
{
	int		x;
	int		y;

	pb->sprite_num = 0;
	y = -1;
	while (pb->map_array[++y])
	{
		x = -1;
		while (pb->map_array[y][++x])
			if (pb->map_array[y][x] == '2')
				pb->sprite_num++;
	}
	if (pb->sprite_num > 0)
		if (!(pb->sprite = (t_sprite*)malloc(sizeof(t_sprite)
											* pb->sprite_num)))
			ft_exit_error(17, pb);
}

void	get_sprites(t_all *pb)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	y = -1;
	if (pb->sprite_num > 0)
		while (pb->map_array[++y])
		{
			x = -1;
			while (pb->map_array[y][++x])
				if (pb->map_array[y][x] == '2')
				{
					pb->sprite[i].x = x * MAP + (MAP / 2);
					pb->sprite[i].y = y * MAP + (MAP / 2);
					i++;
				}
		}
}
