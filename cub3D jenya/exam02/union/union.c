/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 10:39:32 by ngonzo            #+#    #+#             */
/*   Updated: 2020/09/17 10:43:19 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		main(int argc, char **argv)
{
	int i,j;
	char tmp[255];
	if (argc == 3)
	{
		i = 0;
		while (i < 255)
			tmp[i++] = 0;
		i = 1;
		while (i < 3)
		{
			j = 0;
			while (argv[i][j])
			{
				if (tmp[(unsigned char)argv[i][j]] == 0)
				{
					write (1, &argv[i][j], 1);
					tmp[(unsigned char)argv[i][j]] = 1;
				}
				j++;
			}
			i++;
		}
	}
	write (1, "\n", 1);
	return (0);
}
