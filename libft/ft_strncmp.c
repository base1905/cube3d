/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 17:21:44 by arannara          #+#    #+#             */
/*   Updated: 2020/05/15 12:15:46 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*s1s;
	unsigned char	*s2s;

	s1s = (unsigned char *)s1;
	s2s = (unsigned char *)s2;
	i = 0;
	while (s1s[i] && s2s[i] && s1s[i] == s2s[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return (s1s[i] - s2s[i]);
}
