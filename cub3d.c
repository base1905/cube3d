/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:53 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 15:41:51 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>


void	ft_fitscreen(t_all *pb)
{
	int res_x;
	int	res_y;

	mlx_get_screen_size(pb->mlx, &res_x, &res_y);
	if (pb->screen_x > res_x)
		pb->screen_x = res_x;
	if (pb->screen_y > res_y)
		pb->screen_y = res_y;

}

void	ft_path(char *s, char **path)
{
	while (*s == ' ')
		s++;
	*path = ft_strdup(s);
}
void	ft_loadtex(t_all *pb)
{
	int i;

	i = 0;
	while (i < 0)
	{
		pb->tex[i].img = mlx_xpm_file_to_image(pb->mlx, pb->path[i], 
			&(pb->tex[i].width), &(pb->tex[i].height));
		if (pb->tex[i].img == NULL)
		{
			ft_putendl_fd("Structure doesn't load", 2);
			ft_exit_error(pb);
		}
		pb->tex[i].addr = mlx_get_data_addr(pb->tex[i].img, 
			&(pb->tex[i].bits_per_pixel), &(pb->tex[i].line_length), &(pb->tex[i].endian));
		
		if (pb->tex[i].addr == NULL)
		{
			ft_putendl_fd("Structure doesn't load", 2);
			ft_exit_error(pb);
		}
		free(pb->path[i]);
		pb->path[i] = NULL;
	}
}



int		ft_processor(t_all *pb)
{
	if (strncmp(pb->line, "R", 1) == 0)
		ft_resolution(pb, pb->line + 1);

	else if (strncmp(pb->line, "NO", 2) == 0)
		ft_path(pb->line + 2, &(pb->path[0]));
	else if (strncmp(pb->line, "SO", 2) == 0)
		ft_path(pb->line + 2, &(pb->path[1]));
	else if (strncmp(pb->line, "WE", 2) == 0)
		ft_path(pb->line + 2, &(pb->path[2]));
	else if (strncmp(pb->line, "EA", 2) == 0)
		ft_path(pb->line + 2, &(pb->path[3]));
	else if (strncmp(pb->line, "S", 1) == 0)
		ft_path(pb->line + 1, &(pb->path[4]));
	else if (strncmp(pb->line, "F", 1) == 0)
		ft_rgb(pb, pb->line + 1, &(pb->rgb_floor));
	else if (strncmp(pb->line, "C", 1) == 0)
		ft_rgb(pb, pb->line + 1, &(pb->rgb_ceiling));
	else if (ft_ismapstring(pb->line))
	{
		ft_mapser(pb);
		return (0);
	}
	else if (ft_strlen(pb->line) > 0)
	{
		ft_putendl_fd("Error! Undefined key in config\n", 2);
		ft_exit_error(pb);
	}
	return (1);
}
void	ft_parcer(t_all *pb)
{
	int i;
	int map_gnl;

	while ((i = get_next_line(pb->fd, &(pb->line))) >= 0)	
	{
		map_gnl = ft_processor(pb);

		if (i == 0 || map_gnl == 0)
		{
			close(pb->fd);
			break ;
		}
		free(pb->line);
		pb->line = NULL;
		
	}
	if (i < 0)
	{
		ft_putstr_fd("GNL ERRNO: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		ft_exit_error(pb);
	}
 
}

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}



void	ft_ceiling_floor(t_all *pb)
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


int	ft_draw_screen(t_all *pb)
{
	mlx_clear_window(pb->mlx, pb->window);
	ft_ceiling_floor(pb);

	cast_rays(pb);

	ft_printmap(pb);
	ft_map_player(pb);
	ft_draw_map_rays(pb);

	mlx_put_image_to_window(pb->mlx, pb->window, pb->img->img, 0, 0);
	return (0);
}

int		ft_key_press(int key, t_all *pb)
{
	if (key == 13)
	{
		if (pb->map_array[(int)(pb->plr->start_y / MAP)][(int)(pb->plr->start_x / MAP)] != '1')
		{
			pb->plr->start_x += cos(pb->plr->dir) * 4;
			pb->plr->start_y -= sin(pb->plr->dir) * 4;
		}
		else
		{
			pb->plr->start_x -= cos(pb->plr->dir);
			pb->plr->start_y += sin(pb->plr->dir);
		}
	}
	if (key == 1)
	{
		pb->plr->start_y += sin(pb->plr->dir) * SPEED;
		pb->plr->start_x -= cos(pb->plr->dir) * SPEED;
	}
	if (key == 0)
		pb->plr->dir += 0.1;;
	if (key == 2)
		pb->plr->dir -= 0.1;;
	if (key == 53)
	{
		mlx_clear_window(pb->mlx, pb->window);
    	mlx_destroy_window(pb->mlx, pb->window);
		exit(0);
	}
	printf("you press key: %i\n",key);
	return (0);
}

void ft_cub_main(t_all *pb)
{
	pb->mlx = mlx_init();
	pb->window = mlx_new_window(pb->mlx, pb->screen_x, pb->screen_y, "cub3D");
	pb->img->img = mlx_new_image(pb->mlx, pb->screen_x, pb->screen_y);
	pb->img->addr = mlx_get_data_addr(pb->img->img, &pb->img->bits_per_pixel, &pb->img->line_length,
								&pb->img->endian);
//	ft_loadtex(pb);
	ft_draw_screen(pb);
	mlx_hook(pb->window, 2, 1L << 0, ft_key_press, pb);
	mlx_loop_hook(pb->mlx, ft_draw_screen, pb);
	mlx_loop(pb->mlx);

}

int		main(int argc, char **argv)
{
	t_all base;
	t_data  img;
	t_player plr;
	t_ray ray;

	base.img = &img;
	base.plr = &plr;
	base.ray = &ray;

	if (argc < 2)
		ft_putendl_fd("Error! No argument with map file", 2);
	else
	{	
		if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) || strlen(argv[1]) < 5)
			ft_putendl_fd("Error! Wrong file extension!", 2);
		if (argc == 3 && !ft_strncmp(argv[2], "--save", 6) && strlen(argv[2]) == 6)
		{
			base.bmp_screenshot = 1;
			ft_putendl_fd("key --save is OK", 2);
		}
		else if (argc > 2)
			ft_putendl_fd("Error! Too many arguments!", 2);
		if ((base.fd = open(argv[1], O_RDONLY)) < 0)
		{
			ft_putstr_fd("ERRNO: ", 2);
			ft_putendl_fd(strerror(errno), 2);
		}
	}

	ft_initstruct(&base);
	ft_parcer(&base);
	base.plr->projection_plan = (base.screen_x / 2) / (tan(FOV / 2));

	ft_fitscreen(&base);
	ft_cub_main(&base);


	return (0);
}