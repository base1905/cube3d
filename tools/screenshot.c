/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:53 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 15:41:51 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	int_to_char(unsigned char *c, int i)
{
	c[0] = (unsigned char)(i);
	c[1] = (unsigned char)(i >> 8);
	c[2] = (unsigned char)(i >> 16);
	c[3] = (unsigned char)(i >> 24);
}

int		bmp_header(int fd, int h, int w, int padsize)
{
	unsigned char	header[54];
	int				filesize;

	filesize = 54 + (w * 3 * h) + (padsize * h);
	ft_bzero(header, 54);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	int_to_char(header + 2, filesize);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	int_to_char(header + 18, w);
	int_to_char(header + 22, h);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	return (!(write(fd, header, 54) < 0));
}

int		bmp_data(int fd, t_all *pb, int padsize)
{
	unsigned char	zero[3];
	int				x;
	int				y;
	int				pixel;

	y = pb->screen_y;
	ft_bzero(zero, 3);
	while (--y >= 0)
	{
		x = -1;
		while (++x < pb->screen_x)
		{
			pixel = *(pb->img->addr_int + x + y * pb->img->line_length / 4);
			if (write(fd, &pixel, 3) < 0)
				return (0);
		}
		if (padsize > 0 && write(fd, &zero, padsize) < 0)
			return (0);
	}
	return (1);
}

int		take_screenshot(t_all *pb)
{
	int padsize;
	int fd;

	ft_draw_screen(pb);
	padsize = (4 - ((int)pb->screen_x * 3) % 4) % 4;
	if ((fd = open("screenshot.bmp",
			O_WRONLY | O_CREAT, 0777 | O_TRUNC | O_APPEND)) < 0)
		return (0);
	bmp_header(fd, pb->screen_y, pb->screen_x, padsize);
	bmp_data(fd, pb, padsize);
	close(fd);
	return (1);
}

void	make_screenshot(t_all *pb)
{
	pb->img->addr_int = (int *)mlx_get_data_addr(pb->img->img,
		&pb->img->bits_per_pixel, &pb->img->line_length, &pb->img->endian);
	if (!take_screenshot(pb))
		ft_exit_error(3, pb);
	ft_exit_error(0, pb);
}
