/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:53 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 15:41:51 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	line_drawing(t_all *pb, double slice_height, int txt_nbr,
	double height_diff)
{
	int		y;
	int		y1;
	int		color;
	double	step_y;
	int		i;

	i = 0;
	if (slice_height > pb->screen_y)
	{
		i = (slice_height - pb->screen_y) / 2;
		height_diff = pb->screen_y - slice_height;
		slice_height = pb->screen_y;
	}
	step_y = pb->tex[txt_nbr].height / (slice_height - height_diff);
	
	y = ((pb->screen_y - slice_height + 1) / 2);
	y1 = pb->screen_y - y;
	while (y < y1)
	{
		color = *(pb->tex[txt_nbr].addr + (int)((int)(step_y * i) * pb->tex
			[txt_nbr].line_length / sizeof(int) + pb->texture_x * (pb->tex
				[txt_nbr].bits_per_pixel / 8) / sizeof(int)));
		my_mlx_pixel_put(pb->img, pb->ray->x_line, y, color);
		y++;
		i++;
	}
}

static int	choose_texture(t_all *all)
{
	if (all->ray->what_intersection == 1 && all->ray->is_right)
		return (0);
	if (all->ray->what_intersection == 0 && all->ray->is_up)
		return (1);
	if (all->ray->what_intersection == 1 && all->ray->is_left)
		return (2);
	if (all->ray->what_intersection == 0 && all->ray->is_down)
		return (3);
	return (4);
}

void		draw_vertical_line(t_all *pb, double start)
{
	double	slice_height;
	double	height_diff;
	int		txt_nbr;

	slice_height = 0;
	height_diff = 0;
	pb->ray->ray_intersection = (pb->ray->what_intersection == 0) ?
	pb->ray->intersection_x : pb->ray->intersection_y;
	txt_nbr = choose_texture(pb);
	
	pb->ray->ray_fixed = pb->ray->ray_len * cos(start - pb->plr->dir);

	pb->texture_x = (int)((int)pb->ray->ray_intersection % MAP %
		pb->tex[txt_nbr].width);
	if (pb->ray->ray_fixed != 0)
		slice_height = (int)(MAP * pb->plr->projection_plan /
			pb->ray->ray_fixed);
	line_drawing(pb, slice_height, txt_nbr, height_diff);
}
