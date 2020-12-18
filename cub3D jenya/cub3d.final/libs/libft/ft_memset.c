/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <ngonzo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 10:45:46 by ngonzo            #+#    #+#             */
/*   Updated: 2020/05/15 14:21:20 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*tmp;
	size_t	i;

	tmp = s;
	i = 0;
	while (i < n)
	{
		tmp[i] = c;
		i++;
	}
	return (s);
}