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

# define MAP 64
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
    double		ray_fixed;
	int 		what_intersection;
    double		ray_intersection;
    int 		x_line;
}				t_ray;

typedef struct	s_sprite
{
	float		x;
	float		y;
	float		dist;
	float		dir;
	float		hor_offset;
	float		vert_offset;
	int			size;
	float		delta;
}				t_sprite;

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         *addr_int;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
    int         width;
    int         height;
}               t_data;

typedef struct s_texture
{
	void		*img;
	int 		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	char		*path;
}				t_texture;

typedef struct  s_player {
    double      start_x;
    double      start_y;
    double      dir;
    double      start;
    double      end;
    int			projection_plan;
    char		up;
	char		down;
	char		left;
	char		right;
	char		leftrot;
	char		rightrot;

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
    int         sprite_num;
    int         player_num;
    void        *window;
    void        *mlx;
    t_player    *plr;
    t_data      *img;
    t_texture   tex[5];
    t_ray       *ray;
    t_sprite	*sprite;
}               t_all;

void	ft_initstruct(t_all *pb);
int		ft_ismapstring(char *s);
void	ft_map_parser(t_all *pb);
int		ft_exit_error(int c, t_all *pb);
void	ft_cast_rays(t_all *pb);
void	my_mlx_pixel_put(t_data *img, int x, int y, int color);
void	ft_resolution(t_all *pb, char *s);
void	ft_rgb(t_all *pb, char *s, int *rgb);

void	ft_printmap(t_all *pb);
void 	ft_map_player(t_all *pb);
void	ft_draw_map_rays(t_all *pb);

void	make_screenshot(t_all *pb);
int	    ft_draw_screen(t_all *pb);
void	ft_path(t_all *pb, char *s, char **path);
void	ft_loadtex(t_all *pb);
void    ft_map_adding_space(t_all *pb);
void    ft_mapcheck_horizontal (t_all *pb);
void    ft_mapcheck_vertical (t_all *pb);
void    ft_player_pos_init(t_all *pb);
void    ft_player_pos_dir(t_all *pb);
int     ft_exit_esc(t_all *pb);
void	ft_ceiling_floor(t_all *pb);
int		ft_key_press(int key, t_all *pb);
int		ft_key_release(int key, t_all *pb);
int		ft_movement(t_all *pb);
void	get_sprite_params(t_all *pb);
void	draw_sprite(t_all *pb);
void	find_player(t_all *pb);
void	find_sprites(t_all *pb);
void	get_sprites(t_all *pb);


#endif