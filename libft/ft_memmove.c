/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 22:25:42 by arannara          #+#    #+#             */
/*   Updated: 2020/05/22 22:25:50 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst2;
	unsigned char	*src2;

	if (!dst && !src)
		return (NULL);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		dst2 = (unsigned char*)dst;
		src2 = (unsigned char*)src;
		dst2 = dst2 + len;
		src2 = src2 + len;
		while (len)
		{
			dst2--;
			src2--;
			*dst2 = *src2;
			len--;
		}
	}
	return (dst);
}
