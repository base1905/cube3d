#include "../cub3d.h"

// void	find_player(t_all *pb)
// {
// 	int		y;
// 	int		x;

// 	pb->player_num = 0;
// 	y = -1;
// 	while (pb->map_array[++y])
// 	{
// 		x = -1;
// 		while (pb->map_array[y][++x])
// 			if (0 != ft_strchr("NSEW", pb->map_array[y][x]))
// 			{
// 				pb->plr->start_y = y * MAP + (MAP / 2);
// 				pb->plr->start_x = x * MAP + (MAP / 2);
// 				if (pb->map_array[y][x] == 'N')
// 					pb->plr->dir = M_PI / 2;
// 				else if (pb->map_array[y][x] == 'S')
// 					pb->plr->dir = 3 * M_PI / 2;
// 				else if (pb->map_array[y][x] == 'E')
// 					pb->plr->dir = 0;
// 				else if (pb->map_array[y][x] == 'W')
// 					pb->plr->dir = M_PI;
// 				pb->player_num++;
// 			}
// 	}
// }

void	find_sprites(t_all *pb)
{
	int		x;
	int		y;

	pb->sprite_num = 0;
	y = -1;
	while (pb->map_array[++y])
	{
		x = -1;
		while (pb->map_array[y][++x])
			if (pb->map_array[y][x] == '2')
				pb->sprite_num++;
	}
	if (pb->sprite_num > 0)
		if (!(pb->sprite = (t_sprite*)malloc(sizeof(t_sprite)
											* pb->sprite_num)))
			ft_exit_error(18, pb);
}

void	get_sprites(t_all *pb)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	y = -1;
	if (pb->sprite_num > 0)
		while (pb->map_array[++y])
		{
			x = -1;
			while (pb->map_array[y][++x])
				if (pb->map_array[y][x] == '2')
				{
					pb->sprite[i].x = x * MAP + (MAP / 2);
					pb->sprite[i].y = y * MAP + (MAP / 2);
					i++;
				}
		}
}

// int		parser(int *fd, t_all *pb)
// {
// 	init_before_pars(pb);
// 	parser_config(fd, pb);
// 	parser_map(fd, pb);
// 	close(*fd);
// 	init_after_pars(pb);

// 	find_player(pb);

// 	if (pb->player_num > 1)
// 		put_error("Error\n	--Too many players!--\n", pb);
// 	else if (pb->player_num == 0)
// 		put_error("Error\n	--Player not found!--\n", pb);
	
//  find_sprites(pb);
// 	get_sprites(pb);
// 	return (0);
// }