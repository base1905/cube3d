/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 14:30:58 by arannara          #+#    #+#             */
/*   Updated: 2020/05/16 15:32:09 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION
     The memset() function writes len bytes of value c (converted to an unsigned
     char) to the string b.

RETURN VALUES
     The memset() function returns its first argument.*/

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char *)b)[i] = c;
		i++;
	}
	return (b);
}
