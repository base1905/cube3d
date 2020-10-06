/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 18:20:50 by arannara          #+#    #+#             */
/*   Updated: 2020/05/18 18:21:40 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!src && !dst)
		return (0);
	while (i < size - 1 && src[i] != '\0' && size != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (i < size && size != 0)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}
