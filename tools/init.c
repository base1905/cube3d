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

void		ft_ceiling_floor(t_all *pb)
{
	int x;
	int y;

	y = -1;
	while (++y < pb->screen_y / 2)
	{
		x = -1;
		while (++x < pb->screen_x)
			my_mlx_pixel_put(pb->img, x, y, pb->rgb_ceiling);
	}
	y--;
	while (++y < pb->screen_y)
	{
		x = -1;
		while (++x < pb->screen_x)
			my_mlx_pixel_put(pb->img, x, y, pb->rgb_floor);
	}
}

void		ft_fitscreen(t_all *pb)
{
	int res_x;
	int	res_y;

	mlx_get_screen_size(pb->mlx, &res_x, &res_y);
	if (pb->screen_x > res_x)
		pb->screen_x = res_x;
	if (pb->screen_y > res_y)
		pb->screen_y = res_y;
	pb->plr->projection_plan = (pb->screen_x / 2) / (tan(FOV / 2));
}

static void	ft_initstruct2(t_all *pb)
{
	pb->plr->up = 0;
	pb->plr->down = 0;
	pb->plr->left = 0;
	pb->plr->right = 0;
	pb->plr->leftrot = 0;
	pb->plr->rightrot = 0;
	pb->plr->start_x = -1;
	pb->plr->start_y = -1;
	pb->plr->dir = 0;
}

void		ft_initstruct(t_all *pb)
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
	pb->rgb_floor = -1;
	pb->rgb_ceiling = -1;
	i = -1;
	while (++i < 5)
	{
		pb->path[i] = NULL;
		pb->tex[i].img = NULL;
		pb->tex[i].addr = NULL;
	}
	pb->window = NULL;
	pb->mlx = NULL;
	ft_initstruct2(pb);
}
