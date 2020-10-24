/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:53 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 15:41:51 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_print_map_square(t_data *img, int x, int y)
{
	int x1;
	int x2;
	int y1;
	int y2;

	int back;

	x1 = x * MAP;
	x2 = x1 + MAP;
	y1 = y * MAP;
	y2 = y1 + MAP;
	back = x1;

	while (y1 < y2)
	{
		x1 = back;
			while (x1 < x2)
			{
				my_mlx_pixel_put(img, x1, y1, 0x0075715E);
				x1++;
			}
		y1++;
	}
}

void	ft_printmap(t_all *pb)
{
	int i;
	int j;

	i = 0;
	j = 0;

	while (pb->map_array[j] != NULL)
	{
		i = 0;
		while (pb->map_array[j][i] != '\0')
		{
			if (pb->map_array[j][i] == '0' || pb->map_array[j][i] == 'N' || pb->map_array[j][i] == 'S'
				|| pb->map_array[j][i] == 'W' || pb->map_array[j][i] == 'E')
				ft_print_map_square(pb->img, i, j);
			i++;	
		}
		j++;
	}
}

void 	ft_map_player(t_all *pb)
{	
	int x1, y1, x_begin, x, y;

	x1 = pb->plr->start_x + MAP / 2;
	y1 = pb->plr->start_y + MAP / 2;
	x = pb->plr->start_x - MAP / 2;
	y = pb->plr->start_y - MAP / 2;
	x_begin = x;
	while (y < y1)
	{
		x = x_begin;
		while (x < x1)
		{
			my_mlx_pixel_put(pb->img, x, y, 0x00FD971F);
			x++;
		}
		y++;
	}
}

void	ft_draw_map_rays(t_all *pb)
{
	t_player 	ray;
	double		start;
	double		end;
	
	ray = *pb->plr;
	start = ray.dir - (FOV / 2);
	end = ray.dir + (FOV / 2);
	while(start <= end)
	{
		ray.start_x = pb->plr->start_x;
		ray.start_y = pb->plr->start_y;
		while (pb->map_array[(int)(ray.start_y / MAP)][(int)(ray.start_x / MAP)] != '1')
		{
			ray.start_x += cos(start);
			ray.start_y -= sin(start);	
			my_mlx_pixel_put(pb->img, ray.start_x, ray.start_y, 0x00A6E22E);
		}
		start += (FOV) / pb->screen_x;
	}
}
