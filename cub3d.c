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

void ft_initstruct(t_all *pb)
{
	pb->line = NULL;
	pb->bmp = 0;
	pb->screen_x = 0;
	pb->screen_y = 0;
}

void ft_resolution(t_all *pb, char *s)
{
	while (*s == ' ')
		s++;
	if (!ft_isdigit(*s))
		ft_putendl_fd("Resolution error",2);
	pb->screen_x = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	while (*s == ' ')
		s++;
	pb->screen_y = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	if (*s != '\0')
		ft_putendl_fd("Unacceptable symbol after resolution",2);
		
	printf("%d\n%d", pb->screen_x, pb->screen_y);
	printf("\n");
}

void ft_parcer(t_all *pb)
{
	int gnlreturn;

	while ((gnlreturn = get_next_line(pb->fd, &(pb->line))) > 0)	
	{
		if (strncmp(pb->line, "R", 1) == 0)
			ft_resolution(pb, pb->line + 1);
		else if (ft_strlen(pb->line) > 0)
			free (pb->line);
		pb->line = NULL;
	}
	if (gnlreturn < 0)
	{
		ft_putstr_fd("GNL ERRNO: ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}

}



int main(int argc, char **argv)
{
	t_all base;

	if (argc < 2)
		ft_putendl_fd("Error! No argument with map file", 2);
	else
	{	
		if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) || strlen(argv[1]) < 5)
			ft_putendl_fd("Error! Wrong file extension!", 2);
		if (argc == 3 && !ft_strncmp(argv[2], "--save", 6) && strlen(argv[2]) == 6)
		{
			base.bmp = 1;
			ft_putendl_fd("key --save is OK", 2);
		}
		else if (argc > 2)
			ft_putendl_fd("Error! Too many arguments!", 2);
		if ((base.fd = open(argv[1], O_RDONLY)) < 0)
		{
			ft_putstr_fd("ERRNO: ", 2);
			ft_putendl_fd(strerror(errno), 2);
		}
	}
	ft_initstruct(&base);
	ft_parcer(&base);

	printf("testing %d, %d", base.bmp, base.fd);
	return (0);
}