/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:53 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 15:41:51 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			ft_ismapstring(char *s)
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
			*s == 'N' || *s == 'W' || *s == 'S' || *s == 'E'))
			return (0);
		if (*s == ' ')
			space++;
		s++;
	}
	if (space == l)
		return (0);
	return (1);
}

static void	ft_map_joining(t_all *pb)
{
	char *tmp;

	if (!ft_ismapstring(pb->line))
		ft_exit_error(7, pb);
	if ((int)ft_strlen(pb->line) > pb->map_width)
		pb->map_width = (int)ft_strlen(pb->line);
	tmp = pb->map_string;
	pb->map_string = ft_strjoin(pb->map_string, pb->line);
	free(tmp);
	tmp = pb->map_string;
	pb->map_string = ft_strjoin(pb->map_string, "\n");
	free(tmp);
	pb->map_height++;
	free(pb->line);
	pb->line = NULL;
}

void		ft_map_parser(t_all *pb)
{
	char	*tmp;
	int		i;

	pb->map_width = ft_strlen(pb->line);
	pb->map_height = 1;
	tmp = pb->line;
	pb->map_string = ft_strjoin(pb->line, "\n");
	free(tmp);
	pb->line = NULL;
	while ((i = get_next_line(pb->fd, &(pb->line))) >= 0)
	{
		if (i > 0 || ft_strlen(pb->line) > 0)
			ft_map_joining(pb);
		else
			break ;
	}
	pb->map_array = ft_split(pb->map_string, '\n');
	free(pb->map_string);
	pb->map_string = NULL;
	ft_map_adding_space(pb);
	ft_player_pos_init(pb);
	ft_mapcheck_horizontal(pb);
	ft_mapcheck_vertical(pb);
	find_sprites(pb);
	get_sprites(pb);
}
