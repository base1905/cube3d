/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:53 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 15:41:51 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static double	horizontal_intersection(t_all *pb, double start)
{
	double	x_hor;
	double	y_hor;
	double	x_diff;
	double	y_diff;

	x_hor = 0;
	y_hor = 0;
	y_hor = (int)(pb->plr->start_y / MAP) * MAP;
	y_hor += (pb->ray->is_up) ? -0.001 : MAP;
	x_hor = pb->plr->start_x + (pb->plr->start_y - y_hor) / tan(start);
	x_diff = MAP / tan(start);
	x_diff *= (pb->ray->is_left && x_diff > 0) ? -1 : 1;
	x_diff *= (pb->ray->is_right && x_diff < 0) ? -1 : 1;
	y_diff = (pb->ray->is_up) ? -MAP : MAP;
	while (y_hor / MAP >= 0 && y_hor / MAP < pb->map_height && 
		x_hor / MAP >= 0 && x_hor / MAP < pb->map_width  && 
		pb->map_array[(int)(y_hor / MAP)][(int)(x_hor / MAP)] != '1')
	{
		y_hor += y_diff;
		x_hor += x_diff;
	}
	pb->ray->intersection_x = x_hor;
	return(fabs((pb->plr->start_y - y_hor) / sin(start)));
}

static double	vertical_intersection(t_all *pb, double start)
{
	double	x_vert;
	double	y_vert;
	double	y_diff;
	double	x_diff;

	x_vert = 0;
	y_vert = 0;
	x_vert = (int)(pb->plr->start_x / MAP) * MAP;
	x_vert += (pb->ray->is_right) ? MAP : -0.001;
	y_vert = pb->plr->start_y + (pb->plr->start_x - x_vert) * tan(start);
	y_diff = MAP * tan(start);
	y_diff *= (pb->ray->is_up && y_diff > 0) ? -1 : 1;
	y_diff *= (pb->ray->is_down && y_diff < 0) ? -1 : 1;
	x_diff = (pb->ray->is_left) ? -MAP : MAP;
	while (y_vert / MAP >= 0 && y_vert / MAP < pb->map_height && 
		x_vert / MAP >= 0 && x_vert / MAP < pb->map_width &&
		pb->map_array[(int)(y_vert / MAP)][(int)(x_vert / MAP)] != '1')
	{
		x_vert += x_diff;
		y_vert += y_diff;
	}
	pb->ray->intersection_y = y_vert;
	return (fabs((pb->plr->start_x - x_vert) / cos(start)));
}

static void		get_ray_len(t_all *pb, double start)
{
	double	ray_hor;
	double	ray_vert;

	ray_hor = 0;
	ray_vert = 0;
	pb->ray->what_intersection = 0;
	if (pb->ray->is_up || pb->ray->is_down)
		ray_hor = horizontal_intersection(pb, start);
	if (pb->ray->is_left || pb->ray->is_right)
		ray_vert = vertical_intersection(pb, start);
	if (ray_vert == 0)
		pb->ray->ray_len = ray_hor;
	else if (ray_hor == 0)
	{
		pb->ray->ray_len = ray_vert;
		pb->ray->what_intersection = 1;
	}
	else
	{
		pb->ray->ray_len = (ray_vert < ray_hor) ? ray_vert : ray_hor;
		pb->ray->what_intersection = (ray_vert < ray_hor) ? 1 : 0;
	}
}


void	line_drawing(t_all *pb, double slice_height, int txt_nbr, int texture_x, double height_diff)
{
	int 	y;
	int 	y1;
	int 	color;
	double	step_y;
	int 	i;

	i = 0;
	if (slice_height > pb->screen_y)
	{
		i = (slice_height - pb->screen_y) / 2;
		height_diff = pb->screen_y - slice_height;
		slice_height = pb->screen_y;
	}
	step_y = pb->tex[txt_nbr].height / (slice_height - height_diff);
	y = ((pb->screen_y - slice_height) / 2);
	y1 = pb->screen_y - y - 1;
	while (y < y1)
	{
		color = *(pb->tex[txt_nbr].addr + (int)((int)(step_y * i) * pb->tex
			[txt_nbr].line_length / sizeof(int) + texture_x * (pb->tex
				[txt_nbr].bits_per_pixel / 8) / sizeof(int)));
		my_mlx_pixel_put(pb->img, pb->ray->x_line, y, color);
		y++;
		i++;
	}
}

int	choose_texture(t_all *all)
{
	if (all->ray->what_intersection == 1 && all->ray->is_right)
		return(0);
	if (all->ray->what_intersection == 0 && all->ray->is_up)
		return(1);
	if (all->ray->what_intersection == 1 && all->ray->is_left)
		return(2);
	if (all->ray->what_intersection == 0 && all->ray->is_down)
		return(3);
	return (4);
}

void	draw_vertical_line(t_all *pb, double start)
{
	double 	slice_height;
	int 	texture_x;
	double	height_diff;
	int 	txt_nbr;

	slice_height = 0;
	height_diff = 0;
	pb->ray->ray_intersection = (pb->ray->what_intersection == 0) ? 
	pb->ray->intersection_x : pb->ray->intersection_y;
	txt_nbr = choose_texture(pb);
	pb->ray->ray_fixed = pb->ray->ray_len * cos(start - pb->plr->dir);
	texture_x = (int)((int)pb->ray->ray_intersection % MAP % pb->tex[txt_nbr].width);
	if (pb->ray->ray_fixed != 0)
		slice_height = (int)(MAP * pb->plr->projection_plan / 
			pb->ray->ray_fixed);
	line_drawing(pb, slice_height, txt_nbr, texture_x, height_diff);
}

void	get_ray_direction(t_all *pb, double start)
{
	pb->ray->is_right = 0;
	pb->ray->is_left = 0;
	pb->ray->is_up = 0;
	pb->ray->is_down = 0;
	if (cos(start) > 0)
		pb->ray->is_right = 1;
	else if (cos(start) < 0)
		pb->ray->is_left = 1;
	if (sin(start) > 0)
		pb->ray->is_up = 1;
	else if (sin(start) < 0)
		pb->ray->is_down = 1;
}

void		ft_cast_rays(t_all *pb)
{
	double	start;
	double	end;

	ft_ceiling_floor(pb);
	
	// while (pb->plr->dir >= 2 * M_PI)
	// 	pb->plr->dir -= 2 * M_PI;
	// while (pb->plr->dir <= -2 * M_PI)
	// 	pb->plr->dir += 2 * M_PI;
	start = pb->plr->dir - (FOV / 2);
	end = pb->plr->dir + (FOV / 2);
	pb->ray->x_line = pb->screen_x - 1;
    get_sprite_params(pb);
	while (start <= end && pb->ray->x_line >= 0)
	{
		get_ray_direction(pb, start);
		get_ray_len(pb, start);
		draw_vertical_line(pb, start);

		draw_sprite(pb);

		start += (FOV) / pb->screen_x;
        pb->ray->x_line--;
	}
}
