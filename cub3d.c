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

void		my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int			ft_draw_screen(t_all *pb)
{
	if (pb->bmp_screenshot == 1)
		ft_cast_rays(pb);
	else
	{
		mlx_do_sync(pb->mlx);
		ft_movement(pb);
		pb->plr->dir = pb->plr->dir > 2 * M_PI ?
							pb->plr->dir -= 2 * M_PI : pb->plr->dir;
		pb->plr->dir = pb->plr->dir < -2 * M_PI ?
							pb->plr->dir += 2 * M_PI : pb->plr->dir;
		ft_cast_rays(pb);
		mlx_put_image_to_window(pb->mlx, pb->window, pb->img->img, 0, 0);
	}
	return (0);
}

static void	ft_cub_main(t_all *pb)
{
	pb->mlx = mlx_init();
	pb->img->img = mlx_new_image(pb->mlx, pb->screen_x, pb->screen_y);
	pb->img->addr = mlx_get_data_addr(pb->img->img, &pb->img->bits_per_pixel,
		&pb->img->line_length, &pb->img->endian);
	ft_loadtex(pb);
	if (pb->bmp_screenshot == 1)
		make_screenshot(pb);
	pb->window = mlx_new_window(pb->mlx, pb->screen_x, pb->screen_y, "cub3D");
	mlx_hook(pb->window, 2, 1L << 0, ft_key_press, pb);
	mlx_hook(pb->window, 3, 1L << 1, ft_key_release, pb);
	mlx_hook(pb->window, 17, 1L << 17, ft_exit_esc, pb);
	mlx_loop_hook(pb->mlx, ft_draw_screen, pb);
	mlx_loop(pb->mlx);
}

static void	ft_args(t_all *pb, int argc, char **argv)
{
	if (argc < 2)
		ft_exit_error(20, pb);
	else
	{
		if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5) ||
			strlen(argv[1]) < 5)
			ft_exit_error(13, pb);
		if (argc == 3 && !ft_strncmp(argv[2], "--save", 7) &&
			strlen(argv[2]) == 6)
		{
			pb->bmp_screenshot = 1;
			ft_putendl_fd("key --save is OK", 2);
		}
		else if (argc > 2)
			ft_exit_error(19, pb);
		if ((pb->fd = open(argv[1], O_RDONLY)) < 0)
			ft_putendl_fd(strerror(errno), 2);
	}
}

int			main(int argc, char **argv)
{
	t_all		base;
	t_data		img;
	t_player	plr;
	t_ray		ray;

	base.img = &img;
	base.plr = &plr;
	base.ray = &ray;
	ft_initstruct(&base);
	ft_args(&base, argc, argv);
	ft_parser(&base);
	ft_fitscreen(&base);
	ft_ok(&base);
	ft_cub_main(&base);
	return (0);
}
