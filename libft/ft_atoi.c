/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <base1905@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 17:42:42 by arannara          #+#    #+#             */
/*   Updated: 2020/05/26 20:16:57 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int			i;
	int			znak;
	long int	res;

	i = 0;
	znak = 1;
	res = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			znak = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res * znak > 2147483647)
			return (-1);
		if (res * znak < -2147483648)
			return (0);
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * znak);
}
