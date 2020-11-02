/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:53 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 15:41:51 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_path(t_all *pb, char *s, char **path)
{
	if (*path != NULL)
		ft_exit_error(8, pb);
	while (ft_isspace(*s))
		s++;
	if (*s == '\0')
		ft_exit_error(15, pb);
	if (strncmp(s + ft_strlen(s) - 4, ".xpm", 5) != 0)
		ft_exit_error(16, pb);
	*path = ft_strdup(s);
}

void	ft_loadtex(t_all *pb)
{
	int i;

	i = -1;
	while (++i < 5)
	{
		if (!(pb->tex[i].img = mlx_xpm_file_to_image(pb->mlx, pb->path[i],
			&pb->tex[i].width, &pb->tex[i].height)))
			ft_exit_error(17, pb);
		pb->tex[i].addr = (int *)mlx_get_data_addr(pb->tex[i].img,
			&pb->tex[i].bits_per_pixel, &pb->tex[i].line_length,
			&pb->tex[i].endian);
		free(pb->path[i]);
		pb->path[i] = NULL;
	}
}
