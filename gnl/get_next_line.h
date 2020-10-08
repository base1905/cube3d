/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 00:13:51 by arannara          #+#    #+#             */
/*   Updated: 2020/06/20 00:13:53 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "../libft/libft.h"

# define BUFFER_SIZE 32

size_t	ft_strlen(const char *s);
//char	*ft_strdup(const char *str);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strchr_n(const char *s);
int		get_next_line(int fd, char **line);

#endif
