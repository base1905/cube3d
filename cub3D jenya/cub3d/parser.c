/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 12:33:02 by ngonzo            #+#    #+#             */
/*   Updated: 2020/10/10 14:46:43 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				find_player(t_all *all)
{
	int				y;
	int				x;

	all->check_one_player = 0;
	y = -1;
	while (all->map.map[++y])
	{
		x = -1;
		while (all->map.map[y][++x])
		{
			if (0 != ft_strchr("NSEW", all->map.map[y][x]))
			{
				all->player.y = y * SCALE + (SCALE / 2);
				all->player.x = x * SCALE + (SCALE / 2);
				if (all->map.map[y][x] == 'N')
					all->player.dir = M_PI / 2;
				else if (all->map.map[y][x] == 'S')
					all->player.dir = 3 * M_PI / 2;
				else if (all->map.map[y][x] == 'E')
					all->player.dir = 0;
				else if (all->map.map[y][x] == 'W')
					all->player.dir = M_PI;
				all->check_one_player++;
			}
		}
	}
}

void				find_sprites(t_all *all)
{
	int				x;
	int				y;

	all->sprites_amount = 0;
	y = -1;
	while (all->map.map[++y])
	{
		x = -1;
		while (all->map.map[y][++x])
			if (all->map.map[y][x] == '2')
				all->sprites_amount++;
	}
	if (all->sprites_amount > 0)
		if (!(all->sprite = (t_sprite*)malloc(sizeof(t_sprite) * all->sprites_amount)))
			put_error("Error\n	--malloc from sprites don't work--\n", all);
}

void				get_sprites(t_all *all)
{
	int				x;
	int				y;
	int				i;

	i = 0;
	y = -1;
	if (all->sprites_amount > 0)
		while (all->map.map[++y])
		{
			x = -1;
			while (all->map.map[y][++x])
				if (all->map.map[y][x] == '2')
				{
					all->sprite[i].x = x * SCALE + (SCALE / 2);
					all->sprite[i].y = y * SCALE + (SCALE / 2);
					i++;
				}
		}
}

void				parse_resolution(t_all *all, char *read_line)
{
	int				width;
	int				height;
	int				len;

	len = 1;
	while (read_line[len] == ' ' || read_line[len] == '\t')
		len++;
	width = ft_atoi(&read_line[len]);
	len += ft_nbrlen(width);
	while (read_line[len] == ' ' || read_line[len] == '\t')
		len++;
	height = ft_atoi(&read_line[len]);
	if (ft_nbrlen(width) > 4 || ft_nbrlen(height) > 4)
		put_error("Error\n	--Not correct resolution--\n", all);
	if (all->pars.screen_width == -1 && all->pars.screen_height == -1)
	{
		all->pars.screen_width = width;
		all->pars.screen_height = height;
	}
	free(read_line);
}

void				parse_tex_path(t_all *all, char *read_line)
{
	int				len;
	int				i;

	if (ft_strncmp(read_line, "NO ", 3) == 0)
		i = 0;
	else if (ft_strncmp(read_line, "SO ", 3) == 0)
		i = 1;
	else if (ft_strncmp(read_line, "WE ", 3) == 0)
		i = 2;
	else if (ft_strncmp(read_line, "EA ", 3) == 0)
		i = 3;
	else if (ft_strncmp(read_line, "S ", 2) == 0)
		i = 4;
	len = 2;
	while (read_line[len] == ' ' || read_line[len] == '\t')
		len++;
	all->tex[i].path = &read_line[len];
	free(read_line);
}

int				mix_color(int r, int g, int b)
{
	return(r << 16 | g << 8 | b << 0);
}

void				parse_color(t_all *all, char *read_line)
{
	int				len;
	int				color;
	int				r;
	int				g;
	int				b;

	len = 1;
	while (read_line[len] == ' ' || read_line[len] == '\t')
		len++;
	r = ft_atoi(&read_line[len]);
	len += ft_nbrlen(r);
	while (read_line[len] != ',')
		len++;
	g = ft_atoi(&read_line[++len]);
	len += ft_nbrlen(g);
	while (read_line[len] != ',')
		len++;
	b = ft_atoi(&read_line[++len]);
	len += ft_nbrlen(b);
	color = mix_color(r, g, b);
	if (ft_strncmp(read_line, "F ", 2) == 0)
		all->pars.color_bot = color;
	else if (ft_strncmp(read_line, "C ", 2) == 0)
		all->pars.color_top = color;
	free(read_line);
}

void				parse_config_line(t_all *all, char *read_line)
{
	char	*buffer;

	read_line = ft_strtrim(buffer = read_line, "\t \n\v\f\r");
	if (ft_strncmp(read_line, "R ", 2) == 0)
		parse_resolution(all, read_line);
	else if (ft_strncmp(read_line, "F ", 2) == 0 ||
			 ft_strncmp(read_line, "C ", 2) == 0)
		parse_color(all, read_line);
	else if (ft_strncmp(read_line, "NO ", 3) == 0 ||
			 ft_strncmp(read_line, "SO ", 3) == 0 ||
			 ft_strncmp(read_line, "WE ", 3) == 0 ||
			 ft_strncmp(read_line, "EA ", 3) == 0 ||
			 ft_strncmp(read_line, "S ", 2) == 0)
		parse_tex_path(all, read_line);
}

int			is_parsing_complete(t_all *all)
{
	if (all->pars.screen_width == -1)
		return (0);
	if (all->pars.screen_height == -1)
		return (0);
	if (all->pars.color_top == -1)
		return (0);
	if (all->pars.color_bot == -1)
		return (0);
	if (all->tex[0].path == NULL)
		return (0);
	if (all->tex[1].path == NULL)
		return (0);
	if (all->tex[2].path == NULL)
		return (0);
	if (all->tex[3].path == NULL)
		return (0);
	if (all->tex[4].path == NULL)
		return (0);
	return (1);
}

void					parser_config(int *fd, t_all *all)
{
	char	*read_line;
	int		gnl_result;

	while ((gnl_result = get_next_line(*fd, &read_line)) > 0)
	{
		if (ft_strlen(read_line) > 0)
			parse_config_line(all, read_line);
		free(read_line);
		read_line = NULL;
		if (1 == is_parsing_complete(all))
			break;
	}
	free(read_line);
	if (gnl_result == 0)
		put_error("Error\n	--Some game parameters are missed--\n", all);
	if (gnl_result < 0)
		put_error("Error\n	--Error when reading line from scene file--\n", all);
}

int					parser(int *fd, t_all *all)
{
	init_before_pars(all);
	parser_config(fd, all);
	parser_map(fd, all);
	close(*fd);
	init_after_pars(all);
	find_player(all);
	if (all->check_one_player > 1)
		put_error("Error\n	--Too many players!--", all);
	else if (all->check_one_player == 0)
		put_error("Error\n	--Player not found!--", all);
	find_sprites(all);
	get_sprites(all);

	int i = -1;
	while (all->map.map[++i])
		// ft_putendl_fd(all->map.map[i], 1);
		printf("%s|\n", all->map.map[i]);

	return(0);
}
