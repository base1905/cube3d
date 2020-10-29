/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:53 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 15:41:51 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			ft_key_press(int key, t_all *pb)
{
	if (key == 1 || key == 125)
		pb->plr->down = 1;
	else if (key == 13 || key == 126)
		pb->plr->up = 1;
	else if (key == 0)
		pb->plr->left = 1;
	else if (key == 2)
		pb->plr->right = 1;
	else if (key == 123)
		pb->plr->leftrot = 1;
	else if (key == 124)
		pb->plr->rightrot = 1;
	else if (key == 53)
    {
		mlx_clear_window(pb->mlx, pb->window);
		mlx_destroy_window(pb->mlx, pb->window);
		exit(0);
    }
	return (0);
}

int			ft_key_release(int key, t_all *pb)
{
	if (key == 1 || key == 125)
		pb->plr->down = 0;
	else if (key == 13 || key == 126)
		pb->plr->up = 0;
	else if (key == 0)
		pb->plr->left = 0;
	else if (key == 2)
		pb->plr->right = 0;
	else if (key == 123)
		pb->plr->leftrot = 0;
	else if (key == 124)
		pb->plr->rightrot = 0;

	return (0);
}

void		ft_rotation(t_all *pb, float speed)
{
	if (pb->plr->rightrot == 1)
		pb->plr->dir -= M_PI * (speed / 6);
	if (pb->plr->leftrot == 1)
		pb->plr->dir += M_PI * (speed / 6);
}

void		ft_up_down_left_right(t_all *pb, float speed)
{
	if (pb->plr->up == 1)
	{
		pb->plr->start_y -= sin(pb->plr->dir) * MAP * speed;
		pb->plr->start_x += cos(pb->plr->dir) * MAP * speed;
	}
	if (pb->plr->down == 1)
	{
		pb->plr->start_y += sin(pb->plr->dir) * MAP * speed;
		pb->plr->start_x -= cos(pb->plr->dir) * MAP * speed;
	}
	if (pb->plr->left == 1)
	{
		pb->plr->start_y -= sin(pb->plr->dir + M_PI / 2) * MAP * speed;
		pb->plr->start_x += cos(pb->plr->dir + M_PI / 2) * MAP * speed; 
	}
	if (pb->plr->right == 1)
	{
		pb->plr->start_y += sin(pb->plr->dir + M_PI / 2) * MAP * speed;
		pb->plr->start_x -= cos(pb->plr->dir + M_PI / 2) * MAP * speed;
	}
}

int			ft_movement(t_all *pb)
{
	float	speed;

	speed = 0.1;
	ft_up_down_left_right(pb, speed);
	ft_rotation(pb, speed);
	return (0);
}
