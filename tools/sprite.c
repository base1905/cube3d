/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:53 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 15:41:51 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		sort_sprite(t_all *pb)
{
	int			i;
	t_sprite	tmp;

	i = -1;
	while (++i < pb->sprite_num)
	{
		if (pb->sprite[i].dist < pb->sprite[i + 1].dist)
		{
			tmp = pb->sprite[i];
			pb->sprite[i] = pb->sprite[i + 1];
			pb->sprite[i + 1] = tmp;
			i = -1;
		}
	}
}

static float	fix_delta_angle(float fov_start, float sprite_dir)
{
	float		delta;

	delta = fov_start - sprite_dir;
	if (delta <= -M_PI)
		delta = 2 * M_PI + delta;
	else if (delta >= M_PI)
		delta = delta - 2 * M_PI;
	return (delta);
}

void			get_sprite_params(t_all *pb)
{
	double		start;
	int			i;

	start = pb->plr->dir + (FOV / 2);
	i = -1;
	while (++i < pb->sprite_num)
	{
		pb->sprite[i].dir = atan2(pb->plr->start_y - pb->sprite[i].y,
									pb->sprite[i].x - pb->plr->start_x);
		pb->sprite[i].dist = hypot(pb->sprite[i].y - pb->plr->start_y,
									pb->sprite[i].x - pb->plr->start_x);
		pb->sprite[i].size = (int)((MAP / pb->sprite[i].dist)
										* pb->plr->projection_plan);
		pb->sprite[i].delta = fix_delta_angle(pb->plr->dir + (FOV / 2),
													pb->sprite[i].dir);
		pb->sprite[i].hor_offset = (pb->sprite[i].delta / (FOV /
						pb->screen_x) - pb->sprite[i].size / 2);
		pb->sprite[i].vert_offset = (pb->screen_y / 2
												- pb->sprite[i].size / 2);
	}
	sort_sprite(pb);
}

static int		sprite_color(t_all *pb, int y_line, int i)
{
	int			color;
	int			y_texture;
	int			x_texture;

	y_texture = y_line * (pb->tex[4].height - 1) / (pb->sprite[i].size - 1);
	x_texture = (pb->ray->x_line - pb->sprite[i].hor_offset)
						* (pb->tex[4].width - 1) / (pb->sprite[i].size - 1);
	if (x_texture > 63)
		x_texture = 63;
	color = *(pb->tex[4].addr + (int)((int)y_texture * (pb->tex[4].line_length /
			sizeof(int))
			+ x_texture * ((pb->tex[4].bits_per_pixel / 8) / sizeof(int))));
	return (color);
}

void			draw_sprite(t_all *pb)
{
	int			i;
	int			y_line;
	int			color;

	i = -1;
	while (++i < pb->sprite_num)
	{
		if (pb->sprite[i].size > pb->screen_y)
			pb->sprite[i].size = 0;
		if (pb->ray->x_line >= pb->sprite[i].hor_offset &&
			pb->ray->x_line <= pb->sprite[i].hor_offset + pb->sprite[i].size
			&& pb->sprite[i].dist < pb->ray->ray_len)
		{
			y_line = -1;
			while (++y_line < pb->sprite[i].size)
				if ((color = sprite_color(pb, y_line, i)) != 0x000000)
					my_mlx_pixel_put(pb->img, pb->ray->x_line,
							(int)(pb->sprite[i].vert_offset + y_line), color);
		}
	}
}
