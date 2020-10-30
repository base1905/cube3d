/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:53 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 15:41:51 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_player_pos_dir(t_all *pb)
{
	int y;
	int x;

	y = -1;
	while (pb->map_array[++y])
	{
		x = -1;
		while (pb->map_array[y][++x])
		{
			if (pb->map_array[y][x] == 'N')
				pb->plr->dir = M_PI_2;
			if (pb->map_array[y][x] == 'E')
				pb->plr->dir = 0;
			if (pb->map_array[y][x] == 'S')
				pb->plr->dir = 3 * M_PI_2;
			if (pb->map_array[y][x] == 'W')
				pb->plr->dir = M_PI;
		}
	}
}

void		ft_player_pos_init(t_all *pb)
{
	int y;
	int x;

	y = -1;
	while (pb->map_array[++y])
	{
		x = -1;
		while (pb->map_array[y][++x])
		{
			if (pb->map_array[y][x] == 'N' || pb->map_array[y][x] == 'E' ||
				pb->map_array[y][x] == 'S' || pb->map_array[y][x] == 'W')
			{
				if (pb->plr->start_x == -1 && pb->plr->start_y == -1)
				{
					pb->plr->start_y = y * MAP + MAP / 2;
					pb->plr->start_x = x * MAP + MAP / 2;
				}
				else
					ft_exit_error(4, pb);
			}
		}
	}
	if (pb->plr->start_x == -1 && pb->plr->start_y == -1)
		ft_exit_error(5, pb);
	ft_player_pos_dir(pb);
}

void		ft_mapcheck_horizontal(t_all *pb)
{
	int y;
	int x;

	y = -1;
	while (++y < pb->map_height)
	{
		x = -1;
		while (++x < pb->map_width)
		{
			if (pb->map_array[y][x] == ' ')
				continue ;
			if (pb->map_array[y][x] != '1')
				ft_exit_error(6, pb);
			else
			{
				while (x < pb->map_width && pb->map_array[y][x] != ' ')
					x++;
				if (pb->map_array[y][x - 1] != '1')
					ft_exit_error(6, pb);
			}
		}
	}
}

void		ft_mapcheck_vertical(t_all *pb)
{
	int y;
	int x;

	x = -1;
	while (++x < pb->map_width)
	{
		y = -1;
		while (++y < pb->map_height)
		{
			if (pb->map_array[y][x] == ' ')
				continue ;
			if (pb->map_array[y][x] != '1')
				ft_exit_error(6, pb);
			else
			{
				while (y < pb->map_height && pb->map_array[y][x] != ' ')
					y++;
				if (pb->map_array[y - 1][x] != '1')
					ft_exit_error(6, pb);
			}
		}
	}
}

void		ft_map_adding_space(t_all *pb)
{
	int	y;
	int x;

	y = -1;
	while (pb->map_array[++y] != '\0')
	{
		if ((int)ft_strlen(pb->map_array[y]) < pb->map_width)
		{
			pb->map_string = malloc(sizeof(char) * (pb->map_width + 1));
			ft_memset(pb->map_string, ' ', pb->map_width);
			pb->map_string[pb->map_width] = '\0';
			x = -1;
			while (pb->map_array[y][++x] != '\0')
				pb->map_string[x] = pb->map_array[y][x];
			free(pb->map_array[y]);
			pb->map_array[y] = pb->map_string;
		}
	}
	pb->map_string = NULL;
}
