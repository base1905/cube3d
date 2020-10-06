/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 00:13:51 by arannara          #+#    #+#             */
/*   Updated: 2020/06/20 00:13:53 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

size_t	ft_strlen(const char *s);
char	*ft_strdup(char *str);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strchr_n(const char *s);
int		get_next_line(int fd, char **line);

#endif
