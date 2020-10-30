/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:53 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 15:41:51 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_exit_error3(int c)
{
	if (c == 12)
		ft_putendl_fd("Not RGB digit\n", 2);
	else if (c == 13)
		ft_putendl_fd("Wrong file extension\n", 2);
	else if (c == 14)
		ft_putendl_fd("Undefined symbol in key\n", 2);
	else if (c == 15)
		ft_putendl_fd("No texture path\n", 2);
	else if (c == 16)
		ft_putendl_fd("Wrong extension\n", 2);
	else if (c == 17)
	{
		ft_putstr_fd("Texture/sprite doesn't load. ERRNO: ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else if (c == 19)
		ft_putstr_fd("Too many arguments\n", 2);
	else if (c == 20)
		ft_putstr_fd("No argument with map file\n", 2);
	else if (c == 21)
		ft_putstr_fd("Wrong RGB color\n", 2);
}

static void	ft_exit_error2(int c)
{
	if (c == 2)
	{
		ft_putstr_fd("GNL ERRNO: ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else if (c == 3)
		ft_putendl_fd("Screenshot error!\n", 2);
	else if (c == 4)
		ft_putendl_fd("Too many players\n", 2);
	else if (c == 5)
		ft_putendl_fd("No player\n", 2);
	else if (c == 6)
		ft_putendl_fd("Not closed map\n", 2);
	else if (c == 7)
		ft_putendl_fd("Undefined symbol in/after map\n", 2);
	else if (c == 8)
		ft_putendl_fd("Dublicate flag\n", 2);
	else if (c == 9)
		ft_putendl_fd("Resolution error\n", 2);
	else if (c == 10)
		ft_putendl_fd("Unacceptable symbol in/after resolution\n", 2);
	else if (c == 11)
		ft_putendl_fd("Resolution is too big or too small\n", 2);
	else
		ft_exit_error3(c);
}

void		ft_exit_error(int c, t_all *pb)
{
	int i;

	if (c == 1)
		ft_putendl_fd("Error! Undefined key in config\n", 2);
	else
		ft_exit_error2(c);
	i = -1;
	while (++i < 5)
	{
		free(pb->path[i]);
		if (pb->tex[i].img != NULL)
			mlx_destroy_image(pb->mlx, pb->tex[i].img);
	}
	free(pb->line);
	free(pb->map_string);
	if (pb->map_array != NULL)
	{
		i = 0;
		while (i < pb->map_height)
			free(pb->map_array[i++]);
		free(pb->map_array);
	}
	if (pb->bmp_screenshot == 1)
		exit(0);
	exit(c);
}

int			ft_exit_esc(t_all *pb)
{
	int i;

	i = -1;
	while (++i < 5)
	{
		free(pb->path[i]);
		if (pb->tex[i].img != NULL)
			mlx_destroy_image(pb->mlx, pb->tex[i].img);
	}
	free(pb->line);
	free(pb->map_string);
	if (pb->map_array != NULL)
	{
		i = 0;
		while (i < pb->map_height)
			free(pb->map_array[i++]);
		free(pb->map_array);
	}
	if (pb->bmp_screenshot == 1)
		exit(0);
	exit(0);
	return (0);
}
