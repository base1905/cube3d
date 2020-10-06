/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 19:43:03 by arannara          #+#    #+#             */
/*   Updated: 2020/05/22 15:13:15 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1s;
	unsigned char	*s2s;

	s1s = (unsigned char *)s1;
	s2s = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1s[i] != s2s[i])
			return (s1s[i] - s2s[i]);
		i++;
	}
	return (0);
}
