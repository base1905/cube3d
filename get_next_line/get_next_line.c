/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 00:13:21 by arannara          #+#    #+#             */
/*   Updated: 2020/06/20 00:13:30 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_n_check(char **lastbuf, char **line, char *n_pointer)
{
	char *temp;

	*n_pointer = '\0';
	n_pointer++;
	temp = ft_strdup(n_pointer);
	*line = ft_strdup(*lastbuf);
	free(*lastbuf);
	*lastbuf = temp;
	return (1);
}

static int	ft_result(char **lastbuf, char **line, ssize_t reading)
{
	char *n_pointer;

	if (reading == -1)
		return (-1);
	if (*lastbuf && (n_pointer = ft_strchr_n(*lastbuf)))
		return (ft_n_check(lastbuf, line, n_pointer));
	if (*lastbuf)
	{
		*line = *lastbuf;
		*lastbuf = NULL;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*lastbuf[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	ssize_t		reading;
	char		*n_pointer;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	while ((reading = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[reading] = '\0';
		lastbuf[fd] = ft_strjoin_free(lastbuf[fd], buf);
		if ((n_pointer = ft_strchr_n(lastbuf[fd])))
			return (ft_n_check(&lastbuf[fd], &*line, n_pointer));
	}
	return (ft_result(&lastbuf[fd], &*line, reading));
}
