/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 18:07:45 by arannara          #+#    #+#             */
/*   Updated: 2020/05/21 22:38:21 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = ft_strlen((char*)str);
	new = (char*)malloc(sizeof(*str) * (len + 1));
	if (!new)
		return (NULL);
	while (i <= len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
