/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 23:58:20 by arannara          #+#    #+#             */
/*   Updated: 2020/05/21 00:07:20 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	ch;
	char			c;

	c = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ch = -n;
	}
	else
		ch = n;
	if (ch >= 10)
		ft_putnbr_fd(ch / 10, fd);
	c = (ch % 10) + '0';
	ft_putchar_fd(c, fd);
}
