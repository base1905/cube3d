/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 20:50:10 by arannara          #+#    #+#             */
/*   Updated: 2020/10/05 10:36:58 by df               ###   ########.fr       */
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

int main(int argc, char *argv[])
{
	int mas[255];
	int code_num;
	int i;
	int j;

	if (argc == 3)
	{
		i = 0;
		while (i < 255)
			mas[++i] = 0;
		i = 1;
		while(i < 3)
		{
			j = 0;
			while (argv[i][j])
			{
				if (!mas[(int)argv[i][j]])
				{	
					mas[(int)argv[i][j]] = 1;
					write(1, &argv[i][j], 1);
				}
				j++;
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
