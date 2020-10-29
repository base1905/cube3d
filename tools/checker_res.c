/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_res.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:53 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 15:41:51 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_resolution(t_all *pb, char *s)
{
	if (pb->screen_x != 0 && pb->screen_y != 0)
		ft_exit_error(8, pb);
	while (*s == ' ')
		s++;
	if (!ft_isdigit(*s))
			ft_exit_error(9, pb);
	pb->screen_x = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	while (*s == ' ')
		s++;
	pb->screen_y = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	if (*s != '\0')
		ft_exit_error(10, pb);
	if (pb->screen_x < 4 || pb->screen_y < 4)
		ft_exit_error(11, pb);
}

int		ft_rgb2int(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

void	ft_rgb(t_all *pb, char *s, int *rgb)
{
	int i;
	int digit[3];

	i = 0;
	while (*s && i < 3)
	{
		while (*s == ' ')
			s++;
		if (ft_isdigit(*s) && ft_atoi(s) >= 0 && ft_atoi(s) < 256)
			digit[i] = ft_atoi(s);
		else
			ft_exit_error(12, pb);
		while (ft_isdigit(*s))
			s++;
		if (*s == ',')
			s++;
		i++;
	}
	*rgb = ft_rgb2int(0, digit[0], digit[1], digit[2]); 
	
}