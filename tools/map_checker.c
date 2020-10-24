/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:53 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 15:41:51 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

static void ft_player_pos_init (t_all *pb)
{
    int i;
    int j;

	i = 0;
	while (i < pb->map_height)
	{
		j = 0;
		while (j < pb->map_width)
		{
			if (pb->map_array[i][j] == 'N' || pb->map_array[i][j] == 'E' ||
				pb->map_array[i][j] == 'S' || pb->map_array[i][j] == 'W')
				{
					if (pb->plr->start_x == -1.0 && pb->plr->start_y == -1.0)
						{
							pb->plr->start_x = i * MAP + MAP / 2;
							pb->plr->start_y = j * MAP + MAP / 2;

							if (pb->map_array[i][j] == 'N') 
								pb->plr->dir = M_PI_2;
							if (pb->map_array[i][j] == 'E') 
								pb->plr->dir = 0;
							if (pb->map_array[i][j] == 'S') 
								pb->plr->dir = 3 * M_PI_2;
							if (pb->map_array[i][j] == 'W') 
								pb->plr->dir = M_PI;
						}
					else
					{
						ft_putendl_fd("Too many players\n",2);
						ft_exit_error(pb);
					}
				}
			j++;
		}
		i++;
	}
	if (pb->plr->start_x == -1 && pb->plr->start_y == -1)
	{
		ft_putendl_fd("No player\n",2);
		ft_exit_error(pb);
	}
}

void ft_map_adding_space(t_all *pb)
{
	int	i;
	int j;

	i = 0;
	while (pb->map_array[i] != '\0') 
	{
		if ((int)ft_strlen(pb->map_array[i]) < pb->map_width)
		{
			pb->map_string = malloc(sizeof(char) * (pb->map_width + 1));
			ft_memset(pb->map_string, ' ', pb->map_width);
			pb->map_string[pb->map_width] = '\0';
			j = 0;
			while (pb->map_array[i][j] != '\0')
			{
				pb->map_string[j] = pb->map_array[i][j];
				j++; 
			}
			free(pb->map_array[i]);
			pb->map_array[i] = pb->map_string;
		}
		i++;
	}
	pb->map_string = NULL;
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
	pb->map_string = ft_strjoin(pb->line, "\n");
	free(tmp);
	pb->line = NULL;

	while ((i = get_next_line(pb->fd, &(pb->line))) >= 0)
	{
		if ( i > 0 || ft_strlen(pb->line) > 0)
		{
			if (!ft_ismapstring(pb->line))
			{
				ft_putendl_fd("Error! Undefined key in/after map\n",2);
				ft_exit_error(pb);
			}
			if ((int)ft_strlen(pb->line) > pb->map_width)
				pb->map_width = (int)ft_strlen(pb->line);
			tmp = pb->map_string;
			pb->map_string = ft_strjoin(pb->map_string, pb->line);
			free(tmp);
			tmp = pb->map_string;
			pb->map_string = ft_strjoin(pb->map_string,"\n");
			free(tmp);
			pb->map_height++;
			free(pb->line);
			pb->line = NULL;
		}
		else
			break ;
	}
	pb->map_array = ft_split(pb->map_string, '\n');
	free(pb->map_string);
	pb->map_string = NULL;
	ft_map_adding_space(pb);
	ft_player_pos_init(pb);

}