/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 13:34:22 by ngonzo            #+#    #+#             */
/*   Updated: 2020/10/22 13:34:26 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char		*dst;

	dst = data->addr + (y * data->lenl + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void		background(t_all *all)
{
	int		x;
	int		y;
    int		color;

    color = all->pars.color_top;
	y = -1;
    while (++y < all->pars.screen_height / 2)
    {
        x = -1;
        while (++x < all->pars.screen_width)
            my_mlx_pixel_put(&all->data, x, y, color);
    }
    color = all->pars.color_bot;
    while (++y < all->pars.screen_height)
    {
        x = -1;
        while (++x < all->pars.screen_width)
            my_mlx_pixel_put(&all->data, x, y, color);
    }
}

int	choose_texture(t_all *all)
{
	if (all->ray.what_intersection == 1 && all->ray.is_right)
		return(0);
	if (all->ray.what_intersection == 0 && all->ray.is_up)
		return(1);
	if (all->ray.what_intersection == 1 && all->ray.is_left)
		return(2);
	if (all->ray.what_intersection == 0 && all->ray.is_down)
		return(3);
	return (4);
}

void	draw_vertical_line(t_all *all, int x_line)
{
	int 	y;
	int 	y1;
	double 	slice_height;
	int 	color;
	double	ray_intersection;
	double	step_y;
	int 	i;
	int 	texture_x;
	double	height_diff;
	int 	txt_nbr;

	slice_height = 0;
	i = 0;
	height_diff = 0;
	ray_intersection = (all->ray.what_intersection == 0) ? all->ray.intersection_x : all->ray.intersection_y;
	txt_nbr = choose_texture(all);
	texture_x = (int)ray_intersection % SCALE % (all->tex[txt_nbr].width);
	if (all->ray.ray_len != 0)
		slice_height = (int)(SCALE * all->player.projection_plane / all->ray.ray_len);
	if (slice_height > all->pars.screen_height)
	{
		i = (slice_height - all->pars.screen_height) / 2;
		height_diff = all->pars.screen_height - slice_height;
		slice_height = all->pars.screen_height;
	}
	step_y = all->tex[txt_nbr].height / (slice_height - height_diff); 
	y = ((all->pars.screen_height - slice_height) / 2);
	y1 = all->pars.screen_height - y - 1;
	while (y < y1)
	{
		color = *(all->tex[txt_nbr].addr + (int)((int)(step_y * i) * all->tex[txt_nbr].lenl / sizeof(int) + texture_x * (all->tex[txt_nbr].bpp / 8) / sizeof(int)));
		my_mlx_pixel_put(&all->data, x_line, y, color);
		y++;
		i++;
	}
}

static double	horizontal_intersection(t_all *all, double start)
{
	double	x_hor;
	double	y_hor;
	double	x_diff;
	double	y_diff;

	x_hor = 0;
	y_hor = 0;
	y_hor = (int)(all->player.y / SCALE) * SCALE;
	y_hor += (all->ray.is_up) ? -0.001 : SCALE;
	x_hor = all->player.x + (all->player.y - y_hor) / tan(start);
	x_diff = SCALE / tan(start);
	x_diff *= (all->ray.is_left && x_diff > 0) ? -1 : 1;
	x_diff *= (all->ray.is_right && x_diff < 0) ? -1 : 1;
	y_diff = (all->ray.is_up) ? -SCALE : SCALE;
	while (y_hor / SCALE >= 0 && y_hor / SCALE < all->map.max_y && 
		x_hor / SCALE >= 0 && x_hor / SCALE < all->map.max_x && 
		all->map.map[(int)(y_hor / SCALE)][(int)(x_hor / SCALE)] != '1')
	{
		y_hor += y_diff;
		x_hor += x_diff;
	}
	all->ray.intersection_x = x_hor;
	return(fabs((all->player.y - y_hor) / sin(start)));
}

static double	vertical_intersection(t_all *all, double start)
{
	double	x_vert;
	double	y_vert;
	double	y_diff;
	double	x_diff;

	x_vert = 0;
	y_vert = 0;
	x_vert = (int)(all->player.x / SCALE) * SCALE;
	x_vert += (all->ray.is_right) ? SCALE : -0.001;
	y_vert = all->player.y + (all->player.x - x_vert) * tan(start);
	y_diff = SCALE * tan(start);
	y_diff *= (all->ray.is_up && y_diff > 0) ? -1 : 1;
	y_diff *= (all->ray.is_down && y_diff < 0) ? -1 : 1;
	x_diff = (all->ray.is_left) ? -SCALE : SCALE;
	while (y_vert / SCALE >= 0 && y_vert / SCALE < all->map.max_y && 
		x_vert / SCALE >= 0 && x_vert / SCALE < all->map.max_x &&
		all->map.map[(int)(y_vert / SCALE)][(int)(x_vert / SCALE)] != '1')
	{
		x_vert += x_diff;
		y_vert += y_diff;
	}
	all->ray.intersection_y = y_vert;
	return (fabs((all->player.x - x_vert) / cos(start)));
}

static void		get_ray_len(t_all *all, double start)
{
	double		ray_hor;
	double		ray_vert;

	ray_hor = 0;
	ray_vert = 0;
	all->ray.what_intersection = 0;
	if (all->ray.is_up || all->ray.is_down)
		ray_hor = horizontal_intersection(all, start);
	if (all->ray.is_left || all->ray.is_right)
		ray_vert = vertical_intersection(all, start);
	if (ray_vert == 0)
		all->ray.ray_len = ray_hor;
	else if (ray_hor == 0)
	{
		all->ray.ray_len = ray_vert;
		all->ray.what_intersection = 1;
	}
	else
	{
		all->ray.ray_len = (ray_vert < ray_hor) ? (ray_vert * cos(start - 
			all->player.dir)) : (ray_hor * cos(start - all->player.dir));
		all->ray.what_intersection = (ray_vert < ray_hor) ? 1 : 0;
	}
}

void			get_ray_direction(t_all *all, double start)
{
	all->ray.is_right = 0;
	all->ray.is_left = 0;
	all->ray.is_up = 0;
	all->ray.is_down = 0;
	if (cos(start) > 0)
		all->ray.is_right = 1;
	else if (cos(start) < 0)
		all->ray.is_left = 1;
	if (sin(start) > 0)
		all->ray.is_up = 1;
	else if (sin(start) < 0)
		all->ray.is_down = 1;
}

void			draw_scene(t_all *all)
{
	double		start;
	double		end;
	int			x_line;

	background(all);
	start = all->player.dir - (FOV / 2);
	end = all->player.dir + (FOV / 2);
	x_line = all->pars.screen_width - 1;
	get_sprite_params(all);
	while (start <= end && x_line >= 0)
	{
		get_ray_direction(all, start);
		get_ray_len(all, start);
		draw_vertical_line(all, x_line);
		draw_sprite(all, x_line);
		start += (FOV) / all->pars.screen_width;
		x_line--;
	}
}

int				render_next_frame(t_all *all)
{
	if (all->screenshot == 1)
		draw_scene(all);
	else
	{
		mlx_do_sync(all->data.mlx);
		move(all);
		all->player.dir = all->player.dir > 2 * M_PI ? 
						all->player.dir -= 2 * M_PI : all->player.dir;
		all->player.dir = all->player.dir < -2 * M_PI ? 
						all->player.dir += 2 * M_PI : all->player.dir;
		draw_scene(all);
		mlx_put_image_to_window(all->data.mlx, all->data.win, all->data.img, 0, 0);
	}
	return (0);
}

void			cub3D(t_all *all)
{
	all->data.mlx = mlx_init();
	all->data.img = mlx_new_image(all->data.mlx, all->pars.screen_width, 
												all->pars.screen_height);
	all->data.addr = mlx_get_data_addr(all->data.img, &all->data.bpp, 
										&all->data.lenl, &all->data.en);
	textures_init(all);
	if (all->screenshot == 1)
		make_screenshot(all);
	all->data.win = mlx_new_window(all->data.mlx, all->pars.screen_width, 
							all->pars.screen_height, "nedoCUBpochti3D");
	mlx_hook(all->data.win, 2, 1L<<0, key_press, all);
	mlx_hook(all->data.win, 3, 1L<<1, key_release, all);
	mlx_hook(all->data.win, 17, 1L << 17, ft_close, all);
	mlx_loop_hook(all->data.mlx, render_next_frame, all);
	mlx_loop(all->data.mlx);
}

int				main(int argc, char **argv)
{
	t_all		all;
	int			fd;
	
	all.screenshot = 0;
	if(argc == 3 && ft_strncmp(argv[2], "--save", 7) == 0)
		all.screenshot = 1;
	else if (argc != 2)
		put_error("Error\n	--Not correct argumet--\n", &all);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		put_error("Error\n	--Map is not find--\n", &all);
	parser(&fd, &all);
	cub3D(&all);
	return (0);
}
