/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 11:25:55 by arannara          #+#    #+#             */
/*   Updated: 2020/05/22 14:05:43 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	size_t	slen;
	char	*dst;
	char	*str;

	dst = (char *)haystack;
	str = (char *)needle;
	if (*str == '\0')
		return (dst);
	slen = ft_strlen(str);
	i = 0;
	while (*dst != '\0')
	{
		if (i + slen > len)
			return (NULL);
		if (ft_strncmp(dst, str, slen) == 0)
			return (dst);
		dst++;
		i++;
	}
	return (NULL);
}
