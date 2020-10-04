/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 20:50:10 by arannara          #+#    #+#             */
/*   Updated: 2020/10/04 18:10:19 by df               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return(i);
}

void ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int check(char *str, int len, char check)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (str[i] == check)
			return (0);
		i++;
	}
	return(1);
}

int main(int argc, char *argv[])
{
	int i;
	char *str;
	int len;
	int j;

	str = NULL;
	if (argc <= 2 || argc > 3)
		write(1, "\n", 1);
	else
	{
		i = 1;
		len = 0;
		while (argv[i])
		{	
			j = 0;
			while (argv[i][j] != '\0')
			{
				if (check(str, len, argv[i][j]))
				{
					str[len] = argv[i][j];
					len++;
				}
				j++;
			}
			i++;
		}
		str[len] = '\0';
		ft_putstr(str);
	}
	return(0);
}
//https://github.com/alanbarrett2/42-Final-Exam/tree/master/2-0-union
