/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */ 
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 12:46:55 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 14:11:19 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <fcntl.h>
#include <errno.h>
#include <math.h>

#include "minilibx/mlx.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"

# define MAP 16
# define SPEED 4
# define FOV M_PI / 3

typedef struct s_ray
{
	int			is_left;
	int			is_right;
	int			is_up;
	int			is_down;
	double		intersection_x;
	double		intersection_y;
	double		ray_len;
	int 		what_intersection;
}				t_ray;

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
    int         width;
    int         height;
}               t_data;

typedef struct  s_player {
    double      start_x;
    double      start_y;
    double      start_dir;
    double      dir;
    double      start;
    double      end;
    int			projection_plan;

}               t_player;

typedef struct  s_all 
{
    int         bmp_screenshot;
    int         screen_x;
    int         screen_y;

    int         map_height;
    int         map_width;
    int         fd;
    char        *line;
    char        *map_string;
    char        **map_array;

    char        *path[5];
    int         rgb_ceiling;
    int         rgb_floor;
    void        *window;
    void        *mlx;
    t_player    *plr;
    t_data      *img;
    t_data      tex[5];
    t_ray       *ray;
}               t_all;


void	ft_initstruct(t_all *pb);
int		ft_ismapstring(char *s);
void	ft_mapser(t_all *pb);
void	free_struct(t_all *pb);
int		ft_exit_error(t_all *pb);
void	cast_rays(t_all *pb);
void	my_mlx_pixel_put(t_data *img, int x, int y, int color);
void	ft_resolution(t_all *pb, char *s);
void	ft_rgb(t_all *pb, char *s, int *rgb);
void	ft_printmap(t_all *pb);
void 	ft_map_player(t_all *pb);
void	ft_draw_map_rays(t_all *all);



#endif