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

void	ft_initstruct(t_all *pb, t_player *plr)
{
	int i;

	pb->line = NULL;
	pb->bmp = 0;
	pb->screen_x = 0;
	pb->screen_y = 0;
	pb->map_height = 0;
	pb->map_width = 0;
	pb->allmap = NULL;
	pb->map_array = NULL;
	i = -1;
	while (++i < 5)
		pb->path[i] = NULL;
	pb->window = NULL;
	pb->mlx = NULL;

	plr->start_x = 26 * MAP + MAP / 2;
	plr->start_y = 10 * MAP + MAP / 2;
	plr->start_dir = 'N';
	plr->dir = M_PI / 2;

}

void	free_struct(t_all *pb)
{
	int i;

	free (pb->line);
	free (pb->allmap);

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

void	ft_resolution(t_all *pb, char *s)
{
	while (*s == ' ')
		s++;
	if (!ft_isdigit(*s))
		{
			ft_putendl_fd("Resolution error",2);
			ft_exit_error(pb);
		}
	pb->screen_x = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	while (*s == ' ')
		s++;
	pb->screen_y = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	if (*s != '\0')
	{
		ft_putendl_fd("Unacceptable symbol after resolution",2);
		ft_exit_error(pb);
	}
}

int		ft_ismapstring(char *s)
{
	int l;
	int space;
	
	l = ft_strlen(s);
	if (l == 0)
		return (0);
	space = 0;
	while (*s != '\0')
	{
		if (!(*s == '1' || *s == ' ' || *s == '2' || *s == '0' || 
			*s == 'N' || *s == 'W' || *s == 'S' || *s == 'E' ))
			return (0);
		if (*s == ' ')
			space++;
		s++;
	}
	if (space == l)
		return(0);
	return (1);
}

void	ft_mapser(t_all *pb)
{
	char *tmp;
	int i;

	pb->map_width = ft_strlen(pb->line);
	pb->map_height = 1;
		
	tmp = pb->line;
	pb->allmap = ft_strjoin(pb->line, "\n");
	free(tmp);
	pb->line = NULL;

	while ((i = get_next_line(pb->fd, &(pb->line))) >= 0)
	{
		if ( i > 0 || ft_strlen(pb->line) > 0)
		{
			if (!ft_ismapstring(pb->line))
			{
				ft_putendl_fd("Error! Undefined key in map / after map\n",2);
				ft_exit_error(pb);
			}
			if ((int)ft_strlen(pb->line) > pb->map_width)
				pb->map_width = (int)ft_strlen(pb->line);
			tmp = pb->allmap;
			pb->allmap = ft_strjoin(pb->allmap, pb->line);
			free(tmp);
			tmp = pb->allmap;
			pb->allmap = ft_strjoin(pb->allmap,"\n");
			free(tmp);
			pb->map_height++;
			free(pb->line);
			pb->line = NULL;
		}
		else
			break ;
	}
	pb->map_array = ft_split(pb->allmap, '\n');
	free(pb->allmap);
	pb->allmap = NULL;

}

void	ft_path(char *s, char **path)
{
	while (*s == ' ')
		s++;
	*path = ft_strdup(s);
}

int		ft_rgb2int(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

void	ft_rgb(t_all *pb, char *s, int *rgb)
{
	int i;
	int digit[3];

	i = 0;
	while (*s && i < 3)
	{
		while (*s == ' ')
			s++;
		if (ft_isdigit(*s) && ft_atoi(s) >= 0 && ft_atoi(s) < 256)
			digit[i] = ft_atoi(s);
		else
		{
			ft_putendl_fd("Error! Not RGB digit!",2);
			ft_exit_error(pb);
		}
		while (ft_isdigit(*s))
			s++;
		if (*s == ',')
			s++;
		i++;
	}
	*rgb = ft_rgb2int(0, digit[0], digit[1], digit[2]); 
	
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
		printf("Error! Undefined key in config\n");
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
				//img->addr[x1] = 0x00FFFFFF;
				my_mlx_pixel_put(img, x1, y1, 0x00FFFFFF);
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
			if (pb->map_array[j][i] == '0')
				ft_print_map_square(pb->img, i, j);
			i++;	
		}
		j++;
	}
}

void 	ft_rays_map_player(t_all *pb)
{
	t_player	ray = *pb->plr; // копируем координаты луча равные координатам игрока

	float start = ray.dir - M_PI_4; // начало веера лучей
 	float end = ray.dir + M_PI_4; // край веера лучей
	
	while (start <= end)
	{
		ray.start_x = pb->plr->start_x; // каждый раз возвращаемся в точку начала
		ray.start_y = pb->plr->start_y;
		while (pb->map_array[(int)(ray.start_y / MAP)][(int)(ray.start_x / MAP)] != '1')
		{
			ray.start_x += cos(start);
			ray.start_y -= sin(start);
			my_mlx_pixel_put(pb->img, ray.start_x, ray.start_y, 0x00000000);
			
		}
		start += M_PI_2 / 40;
		
	}
			printf("%f, %f ", pb->plr->start_x, pb->plr->start_y);

}


void	ft_draw_image()
{
	pb->img->img = mlx_new_image(pb->mlx, 1024, 768);
	pb->img->addr = mlx_get_data_addr(pb->img->img, &pb->img->bits_per_pixel, &pb->img->line_length,
								&pb->img->endian);

	ft_ceiling_floor(pb);
	ft_printmap(pb);
	ft_rays_map_player(pb);

	ft_walls(pb, ...);
	
}

void ft_draw_window(t_all *pb)
{
	base.window = mlx_new_window(base.mlx, 1024, 768, "Hello world!");

	ft_draw_image();
	
	mlx_put_image_to_window(pb->mlx, pb->window, pb->img->img, 0, 0);
	mlx_destroy_image(pb->mlx, pb->window);
	pb->img->img = NULL;

	mlx_hook(base.window, 2, 1L << 0, &ft_key_press, &base);
    mlx_loop(base.mlx);
}




int	ft_key_press(int key, t_all *pb)
{
	mlx_clear_window(pb->mlx, pb->window);
	if (key == 13)
	{
		if (pb->map_array[(int)floor(pb->plr->start_y) / MAP][(int)floor(pb->plr->start_x) / MAP] != '1')
			{
				if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false)
					posX += dirX * moveSpeed;
      			if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false)
					posY += dirY * moveSpeed;
			}
		
	}
	if (key == 1)
	{
		if (pb->map_array[(int)floor(pb->plr->start_y) / MAP][(int)floor(pb->plr->start_x) / MAP] != '1')
			{
				if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false)
					posX -= dirX * moveSpeed;
     			if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false)
					posY -= dirY * moveSpeed;
			}
	}
	if (key == 0)
		pb->plr->dir += 0.1;
	if (key == 2)
		pb->plr->dir -= 0.1;
	if (key == 53)
	{
		mlx_clear_window(pb->mlx, pb->window);
    	mlx_destroy_window(pb->mlx, pb->window);
		exit(0);
	}
	if (key == 13 || key == 1)
	{

		ft_draw_window(pb);
		mlx_put_image_to_window(pb->mlx, pb->window, pb->img->img, 0, 0);
		mlx_destroy_image(pb->mlx, pb->window);
		pb->img->img = NULL;

	}	
	return (0);
}

ft_walls()
{
	while (x < res_x)
		ft_raycaster(...);


}

void ft_raycaster(t_all *pb, int x)
{
	typedef struct		s_rays
	{
		double			cameraX;
		double			deltaDistX;
		double			deltaDistY;
		double			sideDistX;
		double			sideDistY;
		int				mapX;
		int				mapY;
		int				stepX;
		int				stepY;
	}					t_rays;

	typedef struct	s_camera
	{
		double		posX;
		double		posY;
		double		planeX;
		double		planeY;
		double		dirX;
		double		dirY;
		double		rayDirX;
		double		rayDirY;
		double		perpWallDist;
		int			side;
	}				t_camera;
	
	t_rays r;
	t_camera c;


	//calculate ray position and direction
	r.cameraX = 2 * x / (double)pb->screen_x - 1; //x-coordinate in camera space
	c.rayDirX = c.dirX + c.planeX * r.cameraX;
	c.rayDirY = c.dirY + c.planeY * r.cameraX;
	//which box of the map we're in
	r.mapX = (int)floor(c.posX);
	r.mapY = (int)floor(c.posY);
	//length of ray from one x or y-side to next x or y-side
	r.deltaDistX = fabs(1 / c.rayDirX);
	r.deltaDistY = fabs(1 / c.rayDirY);

	//calculate step and initial sideDist
	if(c.rayDirX < 0)
	{
		r.stepX = -1;
		r.sideDistX = (c.posX - r.mapX) * r.deltaDistX;
	}
	else
	{
		r.stepX = 1;
		r.sideDistX = (r.mapX + 1.0 - c.posX) * r.deltaDistX;
	}
	if(c.rayDirY < 0)
	{
		r.stepY = -1;
		r.sideDistY = (c.posY - r.mapY) * r.deltaDistY;
	}
	else
	{
		r.stepY = 1;
		r.sideDistY = (r.mapY + 1.0 - c.posY) * r.deltaDistY;
	}

     //perform DDA
	while (1)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if(r.sideDistX < r.sideDistY)
		{
			r.sideDistX += r.deltaDistX;
			r.mapX += r.stepX;
			c.side = 0;
		}
		else
		{
			r.sideDistY += r.deltaDistY;
			r.mapY += r.stepY;
			c.side = 1;
		}
		//Check if ray has hit a wall
		if (pb->map_array[r.mapX][r.mapY] == '1')
			break ;
	}

	  //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
	if (c.side == 0) 
		c.perpWallDist = (r.mapX - c.posX + (1 - r.stepX) / 2) / c.rayDirX;
	else
		c.perpWallDist = (r.mapY - c.posY + (1 - r.stepY) / 2) / c.rayDirY;

}




int		main(int argc, char **argv)
{
	t_all base;
	t_data  img;
	t_player plr;

	if (argc < 2)
		ft_putendl_fd("Error! No argument with map file", 2);
	else
	{	
		if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) || strlen(argv[1]) < 5)
			ft_putendl_fd("Error! Wrong file extension!", 2);
		if (argc == 3 && !ft_strncmp(argv[2], "--save", 6) && strlen(argv[2]) == 6)
		{
			base.bmp = 1;
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
	ft_initstruct(&base, &plr);
	ft_parcer(&base);

	printf("%d\n", base.rgb_ceiling);
    
	base.img = &img;
	base.plr = &plr;

	base.mlx = mlx_init();	

	ft_fit_resolution();
    
	ft_initialization();

	ft_draw_window(&base);


}