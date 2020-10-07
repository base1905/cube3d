/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:21:53 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 15:41:51 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>


//void ft_parcer(t_all *base)



int main(int argc, char **argv)
{
	t_all base;

	if (argc < 2)
		ft_putendl_fd("Error! No argument with map file", 2);
	else
	{	
		if (argc == 2 && ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
			ft_putendl_fd("Error! Wrong file extension!", 2);
		if (argc == 3 && !ft_strncmp(argv[2], "--save", 6))
		{
			base.bmp = 1;
			ft_putendl_fd("key --safe is OK", 2);
		}
		else if (argc > 2)
			ft_putendl_fd("Error! Too many arguments!", 2);
		if ((base.fd = open(argv[1], O_RDONLY)) < 0)
			ft_putendl_fd(strerror(errno), 2);
		
	}
	ft_parcer(&base);

	printf("testing %d, %d", base.bmp, base.fd);
	return (0);
}