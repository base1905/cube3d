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

void ft_player_pos_dir (t_all *pb)
{
    int i;
    int j;

	i = -1;
	while (++i < pb->map_height)
	{
		j = -1;
		while (++j < pb->map_width)
		{
			if (pb->map_array[i][j] == 'N') 
				pb->plr->dir = 3 * M_PI_2;
			if (pb->map_array[i][j] == 'E') 
				pb->plr->dir = 0;
			if (pb->map_array[i][j] == 'S') 
				pb->plr->dir = M_PI_2;
			if (pb->map_array[i][j] == 'W') 
				pb->plr->dir = M_PI;
		}
	}
}

void ft_player_pos_init (t_all *pb)
{
    int i;
    int j;

	i = -1;

	while (++i < pb->map_height)
	{
		j = -1;
		while (++j < pb->map_width)
		{
			if (pb->map_array[i][j] == 'N' || pb->map_array[i][j] == 'E' ||
				pb->map_array[i][j] == 'S' || pb->map_array[i][j] == 'W')
				{
					if (pb->plr->start_x == -1 && pb->plr->start_y == -1)
						{
							pb->plr->start_y = i * MAP + MAP / 2;
							pb->plr->start_x = j * MAP + MAP / 2;
						}
					else
						ft_exit_error(4, pb);
				}
		}
	}
	if (pb->plr->start_x == -1 && pb->plr->start_y == -1)
		ft_exit_error(5, pb);
}

void ft_mapcheck_horizontal (t_all *pb)
{
	int i;
	int j;

	i = -1;
	while (++i < pb->map_height)
	{
		j = -1;
		while (++j < pb->map_width)
		{
			if (pb->map_array[i][j] == ' ')
				continue ;
			if (pb->map_array[i][j] != '1')
				ft_exit_error(6, pb);
			else
			{
				while (j < pb->map_width && pb->map_array[i][j] != ' ')
					j++;
				if (pb->map_array[i][j - 1] != '1')
					ft_exit_error(6, pb);
			}
		}
	}
}

void ft_mapcheck_vertical (t_all *pb)
{
	int i;
	int j;

	j = -1;
	while (++j < pb->map_width)
	{
		i = -1;
		while (++i < pb->map_height)
		{
			if (pb->map_array[i][j] == ' ')
				continue ;
			if (pb->map_array[i][j] != '1')
				ft_exit_error(6, pb);
			else
			{
				while (i < pb->map_height && pb->map_array[i][j] != ' ')
					i++;
				if (pb->map_array[i - 1][j] != '1')
					ft_exit_error(6, pb);
			}
		}
	}
}

void ft_map_adding_space(t_all *pb)
{
	int	i;
	int j;

	i = -1;
	while (pb->map_array[++i] != '\0') 
	{
		if ((int)ft_strlen(pb->map_array[i]) < pb->map_width)
		{
			pb->map_string = malloc(sizeof(char) * (pb->map_width + 1));
			ft_memset(pb->map_string, ' ', pb->map_width);
			pb->map_string[pb->map_width] = '\0';
			j = -1;
			while (pb->map_array[i][++j] != '\0')
				pb->map_string[j] = pb->map_array[i][j];
			free(pb->map_array[i]);
			pb->map_array[i] = pb->map_string;
		}
	}
	pb->map_string = NULL;
}
