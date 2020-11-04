/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_processsor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:53 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 15:41:51 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_ok(t_all *pb)
{
	if (pb->screen_x == -1 || pb->screen_y == -1 ||
		pb->rgb_floor == -1 || pb->rgb_ceiling == -1 || pb->map_array == NULL)
		ft_exit_error(23, pb);
}

int		ft_processor(t_all *pb)
{
	if (strncmp(pb->line, "R ", 2) == 0)
		ft_resolution(pb, pb->line + 1);
	else if (strncmp(pb->line, "NO ", 3) == 0)
		ft_path(pb, pb->line + 2, &(pb->path[1]));
	else if (strncmp(pb->line, "SO ", 3) == 0)
		ft_path(pb, pb->line + 2, &(pb->path[3]));
	else if (strncmp(pb->line, "WE ", 3) == 0)
		ft_path(pb, pb->line + 2, &(pb->path[2]));
	else if (strncmp(pb->line, "EA ", 3) == 0)
		ft_path(pb, pb->line + 2, &(pb->path[0]));
	else if (strncmp(pb->line, "S ", 2) == 0)
		ft_path(pb, pb->line + 1, &(pb->path[4]));
	else if (strncmp(pb->line, "F ", 2) == 0)
		ft_rgb(pb, pb->line + 1, &(pb->rgb_floor));
	else if (strncmp(pb->line, "C ", 2) == 0)
		ft_rgb(pb, pb->line + 1, &(pb->rgb_ceiling));
	else if (ft_ismapstring(pb->line))
	{
		ft_map_parser(pb);
		return (0);
	}
	else if (ft_strlen(pb->line) > 0)
		ft_exit_error(1, pb);
	return (1);
}

void	ft_parser(t_all *pb)
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
		ft_exit_error(2, pb);
}
