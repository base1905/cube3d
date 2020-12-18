/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 11:58:48 by ngonzo            #+#    #+#             */
/*   Updated: 2020/10/23 11:58:51 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	textures_init(t_all *all)
{
	all->tex[0].path = "./pics/blue.xpm";
	all->tex[0].img = mlx_xpm_file_to_image(all->data.mlx, 
	all->tex[0].path, &(all->tex[0].width), &(all->tex[0].height));
	all->tex[0].addr = (int *)mlx_get_data_addr(all->tex[0].img, 
	&all->tex[0].bpp, &all->tex[0].lenl, &all->tex[0].en);
	all->tex[1].path = "./pics/brick.xpm";	
	all->tex[1].img = mlx_xpm_file_to_image(all->data.mlx, 
	all->tex[1].path, &(all->tex[1].width), &(all->tex[1].height));
	all->tex[1].addr = (int *)mlx_get_data_addr(all->tex[1].img, 
	&all->tex[1].bpp, &all->tex[1].lenl, &all->tex[1].en);
	all->tex[2].path = "./pics/wood.xpm";	
	all->tex[2].img = mlx_xpm_file_to_image(all->data.mlx, 
	all->tex[2].path, &(all->tex[2].width), &(all->tex[2].height));
	all->tex[2].addr = (int *)mlx_get_data_addr(all->tex[2].img, 
	&all->tex[2].bpp, &all->tex[2].lenl, &all->tex[2].en);
	all->tex[3].path = "./pics/grey.xpm";	
	all->tex[3].img = mlx_xpm_file_to_image(all->data.mlx, 
	all->tex[3].path, &(all->tex[3].width), &(all->tex[3].height));
	all->tex[3].addr = (int *)mlx_get_data_addr(all->tex[3].img, 
	&all->tex[3].bpp, &all->tex[3].lenl, &all->tex[3].en);
	all->tex[4].path = "./pics/pillar.xpm";	
	all->tex[4].img = mlx_xpm_file_to_image(all->data.mlx, 
	all->tex[4].path, &(all->tex[4].width), &(all->tex[4].height));
	all->tex[4].addr = (int *)mlx_get_data_addr(all->tex[4].img, 
	&all->tex[4].bpp, &all->tex[4].lenl, &all->tex[4].en);
}

void	init_after_pars(t_all *all)
{
	all->pars.max_screen_width = 320;
	all->pars.max_screen_height = 240;
	mlx_get_screen_size(all->data.mlx, &all->pars.max_screen_width, 
										&all->pars.max_screen_height);
	if (all->pars.screen_width > all->pars.max_screen_width)
		all->pars.screen_width = all->pars.max_screen_width;
	if (all->pars.screen_height > all->pars.max_screen_height)
		all->pars.screen_height = all->pars.max_screen_height;
	all->player.projection_plane = (all->pars.screen_width / 2) / (tan(FOV / 2));
}

void	init_before_pars(t_all *all)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		all->tex[i].path = NULL;
		all->tex[i].img = NULL;
		all->tex[i].addr = NULL;
		i++;
	}
	all->pars.color_top = -1;//0x00BFFF;
	all->pars.color_bot = -1;//0x654321;
	all->pars.screen_width = -1;// 800
	all->pars.screen_height = -1;//800
	all->player.up = 0;
	all->player.down = 0;
	all->player.left = 0;
	all->player.right = 0;
	all->player.leftrot = 0;
	all->player.rightrot = 0;
	all->player.run = 0;
	all->map.max_x = 0;
	all->map.max_y = 0;
}