/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 10:54:24 by ngonzo            #+#    #+#             */
/*   Updated: 2020/09/17 11:06:46 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *str)
{
	int	len = 0;
	while (str[len])
		len++;
	return (len);
}

int		get_next_line(char **line)
{
	int		i;
	int		r;
	char	*tmp;
	char	c;
	if ((r = read (0, &c, 1)) < 0)
		return (-1);
	if (!(*line = malloc(sizeof(char*))))
		return (0);
	line[0][0] = '\0';
	while (c != '\n' && r != 0)
	{
		i = 0;
		tmp = *line;
		if (!(*line = malloc(sizeof(char*) * (ft_strlen(tmp) + 2))))
			return (-1);
		while (tmp[i] != '\0')
		{
			line[0][i] = tmp[i];
			i++;
		}
		line[0][i] = c;
		line[0][++i] = '\0';
		free(tmp);
		tmp = NULL;
		r = read (0, &c, 1);
	}
	if (r == 0)
		return (0);
	if (c == '\n')
		return (1);
	return (-1);
}
