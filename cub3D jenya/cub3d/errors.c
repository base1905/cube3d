/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 13:51:35 by ngonzo            #+#    #+#             */
/*   Updated: 2020/10/10 14:08:22 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_close()
{
	exit(0);
	return(0);
}

void	put_error(char *message,t_all *all)
{
	// free(all->head);
	write(2, message, ft_strlen(message));
	ft_close(all);
}

void	free_str_array(char **arr)
{
	char **tmp;

	if (arr == NULL)
		return ;
	tmp = arr;
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(tmp);
}

// static	void	free_sprites_images(t_game_params *params)
// {
// 	if (params->sprites)
// 	{
// 		if ((params->mlx) && (params->sprites[0].img.img_ptr))
// 			mlx_destroy_image(params->mlx, params->sprites[0].img.img_ptr);
// 		free(params->sprites[0].img.location_dir);
// 		params->sprites[0].img.img_ptr = NULL;
// 		params->sprites[0].img.location_dir = NULL;
// 	}
// 	free(params->sprites);
// }

// static	void	free_textures_images(t_game_params *params)
// {
// 	int i;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		free(params->textures[i].location_dir);
// 		if ((params->mlx) && (params->textures[i].img_ptr))
// 			mlx_destroy_image(params->mlx, params->textures[i].img_ptr);
// 		params->textures[i].location_dir = NULL;
// 		params->textures[i].img_ptr = NULL;
// 		i++;
// 	}
// }

// void			free_game_params(t_game_params *params)
// {
// 	if ((params->mlx) && (params->buf_img.img))
// 	{
// 		mlx_destroy_image(params->mlx, params->buf_img.img);
// 		params->buf_img.img = NULL;
// 	}
// 	if ((params->window) && (params->mlx))
// 	{
// 		mlx_destroy_window(params->mlx, params->window);
// 		params->window = NULL;
// 	}
// 	free_textures_images(params);
// 	free(params->sprite_texture_dir);
// 	free_sprites_images(params);
// 	free_str_array(params->map);
// 	free(params->hit_distances);
// }